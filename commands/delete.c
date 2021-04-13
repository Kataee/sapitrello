#include "delete.h"

#include "../app/app.h"

#include "../models/board.h"
#include "../models/card.h"
#include "../models/user.h"

#include "../utils/commandutils.h"
#include "../utils/common.h"
#include "../utils/errors.h"
#include "../utils/stringutils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool cmd_delete_card(char *parameters) {
	int target_id = atoi(parameters);

	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	if (!card_list_remove(&(ACTIVE_BOARD->cards), target_id)) {
		print_card_not_found_error(target_id);
		return false;
	}

	ACTIVE_BOARD->card_count--;

	printf("Card deleted successfully.\n");
	return true;
}

bool cmd_delete_board(char *parameters) {
	int target_id = atoi(parameters);
	int active_board_id = ACTIVE_BOARD->id;

	if (!board_list_remove(&(APP_DATABASE.boards), target_id)) {
		print_board_not_found_error(target_id);
		return false;
	}

	if (target_id == active_board_id) {
		ACTIVE_BOARD = NULL;
	}

	printf("Board deleted successfully.\n");
	return true;
}

bool cmd_delete_user(char *parameters) {
	int target_id = atoi(parameters);

	if (user_list_find(APP_DATABASE.users, target_id) == NULL) {
		print_user_not_found_error(target_id);
		return false;
	}

	card_list_node_t *cards_aux = APP_DATABASE.cards;
	while (!card_list_is_empty(cards_aux)) {
		user_list_remove(&(cards_aux->card->assignees), target_id);
		cards_aux = cards_aux->next;
	}

	board_list_node_t *boards_aux = APP_DATABASE.boards;
	while (!board_list_is_empty(boards_aux)) {
		if (user_list_remove(&(boards_aux->board->members), target_id)) {
			boards_aux->board->member_count--;
		}
		boards_aux = boards_aux->next;
	}

	user_list_remove(&(APP_DATABASE.users), target_id);
	APP_DATABASE.user_count--;

	printf("User deleted successfully.\n");
	return true;
}

bool cmd_delete_member(char *parameters) {
	int target_id = atoi(parameters);

	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	if (!user_list_remove(&(ACTIVE_BOARD->members), target_id)) {
		print_user_not_found_error(target_id);
		return false;
	}

	ACTIVE_BOARD->member_count--;

	printf("Member deleted successfully.\n");
	return true;
}

bool cmd_delete(char *parameters) {
	char subcommand[10];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "card") == 0) {
		return cmd_delete_card(subcommand_parameters);
	}

	if (strcmp(subcommand, "board") == 0) {
		return cmd_delete_board(subcommand_parameters);
	}

	if (strcmp(subcommand, "user") == 0) {
		return cmd_delete_user(subcommand_parameters);
	}

	if (strcmp(subcommand, "member") == 0) {
		return cmd_delete_member(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
