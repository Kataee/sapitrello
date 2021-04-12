#include "use.h"

#include "../app/app.h"

#include "../models/board.h"

#include "../utils/commandutils.h"
#include "../utils/errors.h"
#include "../utils/stringutils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool cmd_use_board(char *parameters) {
	int target_id = atoi(parameters);

	board_t *target_board = board_list_find(APP_DATABASE.boards, target_id);
	if (target_board == NULL) {
		print_board_not_found_error(target_id);
		return false;
	}

	ACTIVE_BOARD = target_board;
	printf("Active board changed to %s (%d).\n", target_board->name, target_board->id);
	return true;
}

bool cmd_use(char *parameters) {
	char subcommand[10];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "board") == 0) {
		return cmd_use_board(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
