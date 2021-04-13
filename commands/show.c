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

bool cmd_show_cards() {
	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	if (ACTIVE_BOARD->card_count == 0) {
		printf("Empty set.\n");
		return true;
	}

	printf(
		"\nNumber of cards in board \"%s\" (ID: %d): %d\n\n",
		ACTIVE_BOARD->name,
		ACTIVE_BOARD->id,
		ACTIVE_BOARD->card_count
	);
	__print_single_card(ACTIVE_BOARD->cards);
	printf("\n");

	// TODO: add filters

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

	sscanf(parameters, "%s", subcommand);
	str_tolowercase(subcommand);

	if (strcmp(subcommand, "users") == 0) {
		return cmd_show_users();
	}

	if (strcmp(subcommand, "boards") == 0) {
		return cmd_show_boards();
	}

	if (strcmp(subcommand, "cards") == 0) {
		return cmd_show_cards();
	}

	if (strcmp(subcommand, "members") == 0) {
		return cmd_show_board_members();
	}

	print_syntax_error(parameters);
	return false;
}
