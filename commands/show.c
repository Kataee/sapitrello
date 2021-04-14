#include "show.h"

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

void __print_single_board(board_list_node_t *node) {
	if (node == NULL) {
		return;
	}

	__print_single_board(node->next);
	printf("%5d\t%s\n", node->board->id, node->board->name);
}

void __print_single_user(user_list_node_t *node) {
	if (node == NULL) {
		return;
	}

	__print_single_user(node->next);
	printf("%5d\t%s (%s)\n", node->user->id, node->user->name, node->user->email);
}

void __print_single_card(card_list_node_t *node) {
	if (node == NULL) {
		return;
	}

	__print_single_card(node->next);
	printf("%5d\t%s (status: %s)\n", node->card->id, node->card->title, get_status_name(node->card->status));
}

bool cmd_show_boards() {
	if (APP_DATABASE->board_count == 0) {
		printf("Empty set.\n");
		return true;
	}

	printf("\nNumber of boards: %d\n\n", APP_DATABASE->board_count);
	__print_single_board(APP_DATABASE->boards);
	printf("\n");

	return true;
}

bool cmd_show_users() {
	if (APP_DATABASE->user_count == 0) {
		printf("Empty set.\n");
		return true;
	}

	printf("\nNumber of users: %d\n\n", APP_DATABASE->user_count);
	__print_single_user(APP_DATABASE->users);
	printf("\n");

	return true;
}

bool cmd_show_cards(char *parameters) {
	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	if (ACTIVE_BOARD->card_count == 0) {
		printf("Empty set.\n");
		return true;
	}

	card_list_node_t *result_set = ACTIVE_BOARD->cards;
	int result_count = ACTIVE_BOARD->card_count;

	int token_length;

	char *control_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (control_token == NULL) {
		print_malloc_error("parsing a simple SHOW CARDS WHERE clause");
		return false;
	}

	if (
		sscanf(parameters, "%s%n", control_token, &token_length) == 1 &&
		token_length != 0
	) {
		str_tolowercase(control_token);

		if (strcmp(control_token, "where") != 0) {
			print_syntax_error(control_token);
			free(control_token);
			return false;
		}

		parameters += token_length;

		char *field = (char *) malloc(strlen(parameters) * sizeof(char));
		if (field == NULL) {
			print_malloc_error("parsing a simple SHOW CARDS WHERE [...]");
			free(control_token);
			return false;
		}

		if (
			sscanf(parameters, "%s%n", field, &token_length) != 1 ||
			token_length == 0
		) {
			print_syntax_error(parameters);
			free(control_token);
			free(field);
			return false;
		}

		str_tolowercase(field);
		if (strcmp(field, "title") != 0 && strcmp(field, "status") != 0) {
			print_syntax_error(parameters);
			free(control_token);
			free(field);
			return false;
		}

		parameters += token_length;

		if (
			sscanf(parameters, "%s%n", control_token, &token_length) != 1 ||
			token_length == 0
		) {
			print_syntax_error(parameters);
			free(control_token);
			free(field);
			return false;
		}

		str_tolowercase(control_token);

		if (strcmp(control_token, "is") != 0) {
			print_syntax_error(parameters);
			free(control_token);
			free(field);
			return false;
		}

		parameters += token_length;
		free(control_token);

		char *value = (char *) malloc(strlen(parameters) * sizeof(char));
		if (value == NULL) {
			print_malloc_error("parsing a simple SHOW CARDS WHERE [...] IS [...] clause");
			free(field);
			return false;
		}

		extract_parameter(&parameters, &value);

		result_count = 0;

		if (strcmp(field, "title") == 0) {
			result_set = NULL;

			card_list_node_t *aux = ACTIVE_BOARD->cards;
			while (!card_list_is_empty(aux)) {
				if (strcmp(aux->card->title, value) == 0) {
					card_list_add_front(&result_set, aux->card);
					result_count++;
				}

				aux = aux->next;
			}
		}

		if (strcmp(field, "status") == 0) {
			CARD_STATUS status;
			str_tolowercase(value);

			if (strcmp(value, "todo") == 0) {
				status = TODO;
			} else if (strcmp(value, "doing") == 0) {
				status = DOING;
			} else if (strcmp(value, "done") == 0) {
				status = DONE;
			} else {
				print_syntax_error(value);
				free(field);
				return false;
			}

			result_set = NULL;

			card_list_node_t *aux = ACTIVE_BOARD->cards;
			while (!card_list_is_empty(aux)) {
				if (aux->card->status == status) {
					card_list_add_front(&result_set, aux->card);
					result_count++;
				}

				aux = aux->next;
			}
		}
	}

	printf(
		"\nNumber of cards in board \"%s\" (ID: %d): %d\n\n",
		ACTIVE_BOARD->name,
		ACTIVE_BOARD->id,
		result_count
	);

	__print_single_card(result_set);
	printf("\n");

	return true;
}

bool cmd_show_board_members() {
	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	if (ACTIVE_BOARD->member_count == 0) {
		printf("Empty set.\n");
		return true;
	}

	printf(
		"\nNumber of members in board \"%s\" (ID: %d): %d\n\n",
		ACTIVE_BOARD->name,
		ACTIVE_BOARD->id,
		ACTIVE_BOARD->member_count
	);
	__print_single_user(ACTIVE_BOARD->members);
	printf("\n");

	return true;
}

bool cmd_show(char *parameters) {
	char subcommand[10];
	char *subcommand_parameters;

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	if (strcmp(subcommand, "users") == 0) {
		return cmd_show_users();
	}

	if (strcmp(subcommand, "boards") == 0) {
		return cmd_show_boards();
	}

	get_command_parameters(subcommand, parameters, &subcommand_parameters);

	if (strcmp(subcommand, "cards") == 0) {
		return cmd_show_cards(subcommand_parameters);
	}

	if (strcmp(subcommand, "members") == 0) {
		return cmd_show_board_members();
	}

	print_syntax_error(parameters);
	return false;
}
