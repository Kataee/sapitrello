#include "describe.h"

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

bool cmd_describe_card(char *parameters) {
	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	int target_id = atoi(parameters);

	card_t *target_card = card_list_find(ACTIVE_BOARD->cards, target_id);
	if (target_card == NULL) {
		print_card_not_found_error(target_id);
		return false;
	}

	printf("Title:       %s\n", target_card->title);

	if (strlen(target_card->description) != 0) {
		printf("Description: %s\n", target_card->description);
	}

	printf("Status:      %s\n", get_status_name(target_card->status));
	printf("Assignees:   ");

	if (target_card->assignees == NULL) {
		printf("(unassigned)\n");
		return true;
	}

	user_list_node_t *aux = target_card->assignees;

	printf("\n");

	while (!user_list_is_empty(aux)) {
		printf("%5d\t%s (%s)\n", aux->user->id, aux->user->name, aux->user->email);
		aux = aux->next;
	}

	return true;
}

bool cmd_describe(char *parameters) {
	char subcommand[10];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "card") == 0) {
		return cmd_describe_card(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
