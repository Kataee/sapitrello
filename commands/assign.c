#include "assign.h"

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

bool cmd_assign_user(char *parameters) {
	int target_user_id, target_card_id;
	int chars_read;

	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	if (sscanf(parameters, "%d%n", &target_user_id, &chars_read) != 1) {
		print_syntax_error(parameters);
		return false;
	}

	parameters += chars_read;

	user_t *user = user_list_find(ACTIVE_BOARD->members, target_user_id);
	if (user == NULL) {
		print_user_not_found_error(target_user_id);
		return false;
	}

	char *control_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (control_token == NULL) {
		print_malloc_error("parsing a simple ASSIGN USER [...] TO clause");
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
	if (strcmp(control_token, "card") != 0) {
		print_syntax_error(control_token);
		free(control_token);
		return false;
	}

	parameters += chars_read;
	free(control_token);

	if (sscanf(parameters, "%d%n", &target_card_id, &chars_read) != 1) {
		print_syntax_error(parameters);
		return false;
	}

	card_t *card = card_list_find(ACTIVE_BOARD->cards, target_card_id);
	if (card == NULL) {
		print_card_not_found_error(target_card_id);
		return false;
	}

	user_list_add(&(card->assignees), user);

	printf(
		"Added user \"%s<%s>\" (ID: %d) to board \"%s\" (ID: %d).\n",
		user->name,
		user->email,
		user->id,
		card->title,
		card->id
	);

	return true;
}

bool cmd_assign(char *parameters) {
	char subcommand[10];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "user") == 0) {
		return cmd_assign_user(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
