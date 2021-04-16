#include "select.h"

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

#include <stdbool.h>
#include <stdio.h>

bool cmd_select_card(char *field, char *parameters) {
	int target_card_id;
	int chars_read;

	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	char *control_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (control_token == NULL) {
		print_malloc_error("parsing a simple SELECT [...] FROM clause");
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
	if (strcmp(control_token, "from") != 0) {
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

	if (strcmp(field, "title") == 0) {
		printf("%s\n", card->title);
		return true;
	}

	if (strcmp(field, "description") == 0) {
		if (strlen(card->description) != 0) {
			printf("%s\n", card->description);
		}

		return true;
	}

	if (strcmp(field, "status") == 0) {
		printf("%s\n", get_status_name(card->status));
		return true;
	}

	if (strcmp(field, "assignees") == 0) {
		user_list_node_t *aux = card->assignees;

		while (!user_list_is_empty(aux)) {
			printf("%5d\t%s (%s)\n", aux->user->id, aux->user->name, aux->user->email);
			aux = aux->next;
		}
	}

	return true;
}

bool cmd_select(char *parameters) {
	char subcommand[16];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (
		strcmp(subcommand, "title") == 0 ||
		strcmp(subcommand, "description") == 0 ||
		strcmp(subcommand, "status") == 0 ||
		strcmp(subcommand, "assignees") == 0
	) {
		return cmd_select_card(subcommand, subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
