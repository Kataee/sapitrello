#include "create.h"

#include "../app/app.h"

#include "../models/board.h"

#include "../utils/commandutils.h"
#include "../utils/errors.h"
#include "../utils/stringutils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool cmd_create_user(char *parameters) {
	char *name;
	int chars_read = extract_parameter(&parameters, &name);

	if (chars_read == -1 || strlen(name) == 0) {
		print_user_empty_name_error();
		free(name);
		return false;
	}

	int token_length;
	char *with_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (with_token == NULL) {
		print_malloc_error("parsing a simple CREATE USER [...] WITH clause");
		free(name);
		return false;
	}

	if (
		sscanf(parameters, "%s%n", with_token, &token_length) != 1 ||
		token_length == 0
	) {
		print_user_email_required_error();
		free(name);
		free(with_token);
		return false;
	}

	str_tolowercase(with_token);
	if (strcmp(with_token, "with") != 0) {
		print_syntax_error(with_token);
		free(name);
		free(with_token);
		return false;
	}

	parameters += token_length;

	char *email_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (email_token == NULL) {
		print_malloc_error("parsing a simple CREATE USER [...] WITH EMAIL clause");
		free(name);
		free(with_token);
		return false;
	}

	if (
		sscanf(parameters, "%s%n", email_token, &token_length) != 1 ||
		token_length == 0
	) {
		print_user_email_required_error();
		free(name);
		free(email_token);
		free(with_token);
		return false;
	}

	str_tolowercase(email_token);
	if (strcmp(email_token, "email") != 0) {
		print_syntax_error(email_token);
		free(name);
		free(email_token);
		free(with_token);
		return false;
	}

	parameters += token_length;

	char *email;
	chars_read = extract_parameter(&parameters, &email);

	if (chars_read == -1 || strlen(email) == 0) {
		print_user_email_required_error();
		free(name);
		free(email);
		free(email_token);
		free(with_token);
		return false;
	}

	user_t *user = user_create(name, email);
	if (user == NULL) {
		print_user_create_fail_error();
		free(name);
		free(email);
		free(email_token);
		free(with_token);
		return false;
	}

	user_list_add(&(APP_DATABASE.users), user);
	APP_DATABASE.user_count++;
	printf("Created user \"%s<%s>\" (ID: %d).\n", user->name, user->email, user->id);

	return true;
}

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
	APP_DATABASE.board_count++;
	printf("Created board \"%s\" (ID: %d).\n", board->name, board->id);

	return true;
}

bool cmd_create_card(char *parameters) {
	if (ACTIVE_BOARD == NULL) {
		print_active_board_not_selected_error();
		return false;
	}

	char *title, description[MAX_CARD_DESCRIPTION_LENGTH];
	int chars_read = extract_parameter(&parameters, &title);

	if (chars_read == -1 || strlen(title) == 0) {
		print_card_empty_title_error();
		free(title);
		return false;
	}

	int token_length;
	char *with_token = (char *) malloc(strlen(parameters) * sizeof(char));
	if (with_token == NULL) {
		print_malloc_error("parsing a simple CREATE CARD [...] WITH clause");
		free(title);
		return false;
	}

	if (
		sscanf(parameters, "%s%n", with_token, &token_length) == 1 &&
		token_length != 0
	) {
		str_tolowercase(with_token);

		if (strcmp(with_token, "with") != 0) {
			print_syntax_error(with_token);
			free(title);
			free(with_token);
			return false;
		}

		parameters += token_length;

		char *description_token = (char *) malloc(strlen(parameters) * sizeof(char));
		bool ok = true;

		if (
			sscanf(parameters, "%s%n", description_token, &token_length) != 1 ||
			token_length == 0
		) {
			ok = false;
		}

		if (ok) {
			str_tolowercase(description_token);

			if (strcmp(description_token, "description") != 0) {
				ok = false;
			}
		}

		if (!ok) {
			print_syntax_error(description_token);
			free(title);
			free(with_token);
			free(description_token);
			return false;
		}

		free(with_token);
		free(description_token);

		printf("Please enter a description: ");
		scanf("%[^\n]", &description);
		getchar();
	}

	card_t *card = card_create(title, description);
	if (card == NULL) {
		print_card_create_fail_error();
		free(title);
		return false;
	}

	card_list_add(&(APP_DATABASE.cards), card);
	APP_DATABASE.card_count++;
	card_list_add(&(ACTIVE_BOARD->cards), card);
	ACTIVE_BOARD->card_count++;

	printf("Created card \"%s\" (ID: %d).\n", card->title, card->id);
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

	if (strcmp(subcommand, "user") == 0) {
		return cmd_create_user(subcommand_parameters);
	}

	if (strcmp(subcommand, "card") == 0) {
		return cmd_create_card(subcommand_parameters);
	}

	print_syntax_error(parameters);
	return false;
}
