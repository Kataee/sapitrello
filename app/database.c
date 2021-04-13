#include "database.h"

#include "../models/board.h"
#include "../models/card.h"
#include "../models/user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char MAGIC_NUMBER = 137;

void load_database(database_t **database) {
	FILE *f = fopen("./data.stdb", "rb");

	*database = (database_t *) malloc(sizeof(database_t));

	(*database)->user_count = 0;
	(*database)->board_count = 0;
	(*database)->card_count = 0;

	(*database)->users = NULL;
	(*database)->boards = NULL;
	(*database)->cards = NULL;

	if (f == NULL) {
		return;
	}

	unsigned char magic_number;
	fread(&magic_number, sizeof(unsigned char), 1, f);

	if (magic_number != MAGIC_NUMBER) {
		return;
	}

	char magic_header[5];
	fread(magic_header, sizeof(char), 4, f);

	if (strcmp(magic_header, "SAPI") != 0) {
		return;
	}

	fread(&((*database)->user_count), sizeof(unsigned int), 1, f);
	fread(&((*database)->board_count), sizeof(unsigned int), 1, f);
	fread(&((*database)->card_count), sizeof(unsigned int), 1, f);

	for (int i = 0; i < (*database)->user_count; i++) {
		user_t *user = (user_t *) malloc(sizeof(user_t));

		unsigned int name_length, email_length;

		fread(&(user->id), sizeof(unsigned int), 1, f);
		fread(&name_length, sizeof(unsigned int), 1, f);
		fread(&(user->name), sizeof(char), name_length, f);
		fread(&email_length, sizeof(unsigned int), 1, f);
		fread(&(user->email), sizeof(char), email_length, f);

		user_list_add_front(&((*database)->users), user);

		if (CURRENT_USER_ID == 0) {
			CURRENT_USER_ID = user->id + 1;
		}
	}

	for (int i = 0; i < (*database)->card_count; i++) {
		card_t *card = (card_t *) malloc(sizeof(card_t));

		unsigned int title_length, description_length;

		fread(&(card->id), sizeof(unsigned int), 1, f);
		fread(&title_length, sizeof(unsigned int), 1, f);
		fread(&(card->title), sizeof(char), title_length, f);
		fread(&description_length, sizeof(unsigned int), 1, f);
		fread(&(card->description), sizeof(char), description_length, f);
		fread(&(card->assignee_count), sizeof(unsigned int), 1, f);

		int k = card->assignee_count;

		for (int j = 0; j < k; j++) {
			unsigned int target_id;
			fread(&target_id, sizeof(unsigned int), 1, f);

			user_t *target_user = user_list_find((*database)->users, target_id);

			if (target_user == NULL) {
				card->assignee_count--;
			} else {
				user_list_add_front(&(card->assignees), target_user);
			}
		}

		card_list_add_front(&((*database)->cards), card);

		if (CURRENT_CARD_ID == 0) {
			CURRENT_CARD_ID = card->id + 1;
		}
	}

	for (int i = 0; i < (*database)->board_count; i++) {
		board_t *board = (board_t *) malloc(sizeof(board_t));

		int name_length;

		fread(&(board->id), sizeof(unsigned int), 1, f);
		fread(&name_length, sizeof(unsigned int), 1, f);
		fread(&(board->name), sizeof(char), name_length, f);
		fread(&(board->member_count), sizeof(unsigned int), 1, f);
		fread(&(board->card_count), sizeof(unsigned int), 1, f);

		int k = board->member_count;

		for (int j = 0; j < k; j++) {
			unsigned int target_id;
			fread(&target_id, sizeof(unsigned int), 1, f);

			user_t *target_user = user_list_find((*database)->users, target_id);

			if (target_user == NULL) {
				board->member_count--;
			} else {
				user_list_add_front(&(board->members), target_user);
			}
		}

		k = board->card_count;

		for (int j = 0; j < k; j++) {
			unsigned int target_id;
			fread(&target_id, sizeof(unsigned int), 1, f);

			card_t *target_card = card_list_find((*database)->cards, target_id);

			if (target_card == NULL) {
				board->card_count--;
			} else {
				card_list_add_front(&(board->cards), target_card);
			}
		}

		board_list_add_front(&((*database)->boards), board);

		if (CURRENT_BOARD_ID == 0) {
			CURRENT_BOARD_ID = board->id + 1;
		}
	}

	fclose(f);
}

void save_database(database_t *database) {
	FILE *f = fopen("./data.stdb", "wb");

	if (f == NULL) {
		printf("warning: failed to save the database, file is not writable.\n");
		return;
	}

	fwrite(&MAGIC_NUMBER, sizeof(unsigned char), 1, f);

	char magic_header[] = "SAPI";
	fwrite(magic_header, sizeof(char), 4, f);

	fwrite(&(database->user_count), sizeof(unsigned int), 1, f);
	fwrite(&(database->board_count), sizeof(unsigned int), 1, f);
	fwrite(&(database->card_count), sizeof(unsigned int), 1, f);

	user_list_node_t *aux_user = database->users;
	card_list_node_t *aux_card = database->cards;
	board_list_node_t *aux_board = database->boards;

	while (!user_list_is_empty(aux_user)) {
		unsigned int name_length = strlen(aux_user->user->name);
		unsigned int email_length = strlen(aux_user->user->email);

		fwrite(&(aux_user->user->id), sizeof(unsigned int), 1, f);
		fwrite(&name_length, sizeof(unsigned int), 1, f);
		fwrite(&(aux_user->user->name), sizeof(char), name_length, f);
		fwrite(&email_length, sizeof(unsigned int), 1, f);
		fwrite(&(aux_user->user->email), sizeof(char), email_length, f);
		aux_user = aux_user->next;
	}

	while (!card_list_is_empty(aux_card)) {
		unsigned int title_length = strlen(aux_card->card->title);
		unsigned int description_length = strlen(aux_card->card->description);

		fwrite(&(aux_card->card->id), sizeof(unsigned int), 1, f);
		fwrite(&title_length, sizeof(unsigned int), 1, f);
		fwrite(&(aux_card->card->title), sizeof(char), title_length, f);
		fwrite(&description_length, sizeof(unsigned int), 1, f);
		fwrite(&(aux_card->card->description), sizeof(char), description_length, f);
		fwrite(&(aux_card->card->assignee_count), sizeof(unsigned int), 1, f);

		aux_user = aux_card->card->assignees;

		while (!user_list_is_empty(aux_user)) {
			fwrite(&(aux_user->user->id), sizeof(unsigned int), 1, f);
			aux_user = aux_user->next;
		}

		aux_card = aux_card->next;
	}

	while (!board_list_is_empty(aux_board)) {
		unsigned int name_length = strlen(aux_board->board->name);

		fwrite(&(aux_board->board->id), sizeof(unsigned int), 1, f);
		fwrite(&name_length, sizeof(unsigned int), 1, f);
		fwrite(&(aux_board->board->name), sizeof(char), name_length, f);
		fwrite(&(aux_board->board->member_count), sizeof(unsigned int), 1, f);
		fwrite(&(aux_board->board->card_count), sizeof(unsigned int), 1, f);

		aux_user = aux_board->board->members;

		while (!user_list_is_empty(aux_user)) {
			fwrite(&(aux_user->user->id), sizeof(unsigned int), 1, f);
			aux_user = aux_user->next;
		}

		aux_card = aux_board->board->cards;

		while (!card_list_is_empty(aux_card)) {
			fwrite(&(aux_card->card->id), sizeof(unsigned int), 1, f);
			aux_card = aux_card->next;
		}

		aux_board = aux_board->next;
	}

	fclose(f);
}
