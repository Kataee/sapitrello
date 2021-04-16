#include "update.h"

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

bool cmd_update_card_title(card_t *card, char *parameters) {
	char *title;
	int chars_read = extract_parameter(&parameters, &title);

	if (chars_read == -1 || strlen(title) == 0) {
		print_card_empty_title_error();
		free(title);
		return false;
	}

	if (strlen(title) >= MAX_CARD_TITLE_LENGTH) {
		print_card_title_too_long_error(MAX_CARD_TITLE_LENGTH);
		free(title);
		return false;
	}

	strcpy(card->title, title);
	printf("Title of card with ID %d changed to \"%s\" successfully.\n", card->id, card->title);

	return true;
}

bool cmd_update_card_description(card_t *card) {
	char description[MAX_CARD_DESCRIPTION_LENGTH];
	printf("Please provide the new description of the card: ");
	scanf("%[^\n]", description);
	getchar();

	if (strlen(description) >= MAX_CARD_DESCRIPTION_LENGTH) {
		print_card_description_too_long_error(MAX_CARD_DESCRIPTION_LENGTH);
		return false;
	}

	strcpy(card->description, description);
	printf("Description of card with ID %d updated successfully.\n", card->id);

	return true;
}

bool cmd_update_card_status(card_t *card, char *parameters) {
	str_trim(parameters);
	str_tolowercase(parameters);

	bool ok = false;
	CARD_STATUS new_status;

	if (strcmp(parameters, "todo") == 0) {
		ok = true;
		new_status = TODO;
	}

	if (strcmp(parameters, "doing") == 0) {
		ok = true;
		new_status = DOING;
	}

	if (strcmp(parameters, "done") == 0) {
		ok = true;
		new_status = DONE;
	}

	if (ok) {
		card->status = new_status;
		printf("Status of card with ID %d changed to %s successfully.\n", card->id, get_status_name(card->status));
	} else {
		print_syntax_error(parameters);
	}

	return ok;
}

bool cmd_update_card(char *parameters) {
	int target_card_id;
	int chars_read;

	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	if (sscanf(parameters, "%d%n", &target_card_id, &chars_read) != 1) {
		print_syntax_error(parameters);
		return false;
	}

	parameters += chars_read;

	card_t *card = card_list_find(ACTIVE_BOARD->cards, target_card_id);
	if (card == NULL) {
		print_card_not_found_error(target_card_id);
		return false;
	}

	char *control_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (control_token == NULL) {
		print_malloc_error("parsing a simple UPDATE CARD [...] SET clause");
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
	if (strcmp(control_token, "set") != 0) {
		print_syntax_error(control_token);
		free(control_token);
		return false;
	}

	free(control_token);

	parameters += chars_read;

	char field[16];
	char *subcommand_parameters;

	sscanf(parameters, "%s", field);
	str_tolowercase(field);
	str_trim(parameters);

	if (strcmp(field, "description") == 0) {
		return cmd_update_card_description(card);
	}

	get_command_parameters(field, parameters, &subcommand_parameters);

	if (strcmp(field, "title") == 0) {
		return cmd_update_card_title(card, subcommand_parameters);
	}

	if (strcmp(field, "status") == 0) {
		return cmd_update_card_status(card, subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}

bool cmd_update(char *parameters) {
	char subcommand[20];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "card") == 0) {
		return cmd_update_card(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
