#include "create.h"

#include "../app/app.h"

#include "../models/board.h"

#include "../utils/commandutils.h"
#include "../utils/errors.h"
#include "../utils/stringutils.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool cmd_create_board(char *parameters) {
	str_trim_quotes(parameters);

	if (strlen(parameters) == 0) {
		print_board_empty_name_error();
		return false;
	}

	board_t *board = board_create(parameters);
	if (board == NULL) {
		print_board_create_fail_error();
		return false;
	}

	board_list_add(&(APP_DATABASE.boards), board);
	printf("Created board \"%s\" (%d).\n", board->name, board->id);
	return true;
}

bool cmd_create(char *parameters) {
	char subcommand[10];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "board") == 0) {
		return cmd_create_board(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
