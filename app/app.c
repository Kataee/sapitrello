#include "app.h"
#include "database.h"

#include "../models/board.h"
#include "../parser/stql.h"

#include "../utils/errors.h"
#include "../utils/stringutils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

database_t *APP_DATABASE;
board_t *ACTIVE_BOARD = NULL;
bool is_running = true;

void start_application(int argc, char **argv) {
	load_database(&APP_DATABASE);

	char line[0x1000];

	if (argc > 2) {
		if (strcmp(argv[1], "-i") == 0) {
			char *path = str_concatenate_words(2, argc, argv);
			if (path == NULL) {
				print_malloc_error("parsing the input file path");
				exit(MALLOC_ERROR_CODE);
				return;
			}

			str_trim_quotes(path);
			str_trim(path);

			if (strlen(path) == 0) {
				print_invalid_filename_error();
				exit(INVALID_FILENAME_ERROR_CODE);
				return;
			}

			FILE *fin = fopen(path, "r");
			if (fin == NULL) {
				print_file_not_found_error(path);
				exit(FILE_NOT_FOUND_ERROR_CODE);
				return;
			}

			while (fscanf(fin, "%[^\n] ", line) != EOF) {
				if (!stql_parse(line)) {
					fclose(fin);
					return;
				}
			}

			fclose(fin);
			free(path);
			return;
		}
	}

	bool should_run = true;

	printf("Welcome to sapitrello v%s!\n\n", APP_VERSION);

	printf("Copyright (c) 2021 Otto Tovisi, Napsugar Veress, Jozsef Sallai\n");
	printf("This software is released under the MIT license.\n\n");

	printf("Information about the usage of the app: https://git.io/JOZv3\n\n");

	while (is_running) {
		printf("sapitrello> ");
		scanf("%[^\n]", line);
		getchar();

		stql_parse(line);
	}
}

void stop_application() {
	is_running = false;
}
