#include "add.h"

#include "../app/app.h"

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

bool cmd_add_user(char *parameters) {
	int target_user_id, target_board_id;
	int chars_read;

	if (sscanf(parameters, "%d%n", &target_user_id, &chars_read) != 1) {
		print_syntax_error(parameters);
		return false;
	}

	parameters += chars_read;

	user_t *user = user_list_find(APP_DATABASE.users, target_user_id);
	if (user == NULL) {
		print_user_not_found_error(target_user_id);
		return false;
	}

	char *control_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (control_token == NULL) {
		print_malloc_error("parsing a simple ADD USER [...] TO clause");
		return false;
	}

	if (
		sscanf(parameters, "%s%n", control_token, &chars_read) != 1 ||
		chars_read == 0
	) {
		print_syntax_error(parameters);
		free(control_token);
		return false;
	}

	str_tolowercase(control_token);
	if (strcmp(control_token, "to") != 0) {
		print_syntax_error(control_token);
		free(control_token);
		return false;
	}

	parameters += chars_read;

	if (
		sscanf(parameters, "%s%n", control_token, &chars_read) != 1 ||
		chars_read == 0
	) {
		print_syntax_error(parameters);
		free(control_token);
		return false;
	}

	str_tolowercase(control_token);
	if (strcmp(control_token, "board") != 0) {
		print_syntax_error(control_token);
		free(control_token);
		return false;
	}

	parameters += chars_read;
	free(control_token);

	if (sscanf(parameters, "%d%n", &target_board_id, &chars_read) != 1) {
		print_syntax_error(parameters);
		return false;
	}

	board_t *board = board_list_find(APP_DATABASE.boards, target_board_id);
	if (board == NULL) {
		print_board_not_found_error(target_board_id);
		return false;
	}

	user_list_add(&(board->members), user);
	board->member_count++;

	printf(
		"Added user \"%s<%s>\" (ID: %d) to board \"%s\" (ID: %d).\n",
		user->name,
		user->email,
		user->id,
		board->name,
		board->id
	);

	return true;
}

bool cmd_add(char *parameters) {
	char subcommand[10];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "user") == 0) {
		return cmd_add_user(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
