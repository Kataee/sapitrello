#include "database.h"

#include "../models/board.h"
#include "../models/card.h"
#include "../models/user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char MAGIC_NUMBER = 137;

void load_database(database_t *database) {
	FILE *f = fopen("./data.stdb", "rb");

	database = (database_t *) malloc(sizeof(database_t));

	database->user_count = 0;
	database->board_count = 0;
	database->card_count = 0;

	database->users = NULL;
	database->boards = NULL;
	database->cards = NULL;

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

	fread(&(database->user_count), sizeof(unsigned int), 1, f);
	fread(&(database->board_count), sizeof(unsigned int), 1, f);
	fread(&(database->card_count), sizeof(unsigned int), 1, f);

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

	fclose(f);
}
