#include "errors.h"

#include <stdio.h>

void print_syntax_error(const char *near) {
	printf("ERROR (%d): syntax error near '%s'.\n", SYNTAX_ERROR_CODE, near);
}

void print_malloc_error(const char *during) {
	printf("ERROR (%d): memory allocation error while %s.\n", MALLOC_ERROR_CODE, during);
}

void print_active_board_not_selected_error() {
	printf("ERROR (%d): no active board is selected.\n", ACTIVE_BOARD_NOT_SELECTED_ERROR_CODE);
}

void print_invalid_filename_error() {
	printf("ERROR (%d): invalid file name received.\n", INVALID_FILENAME_ERROR_CODE);
}

void print_file_not_found_error(const char *path) {
	printf("ERROR (%d): file not found: \"%s\".\n", FILE_NOT_FOUND_ERROR_CODE, path);
}

void print_board_not_found_error(int id) {
	printf("ERROR (%d): cannot find board with ID %d.\n", BOARD_NOT_FOUND_ERROR_CODE, id);
}

void print_board_empty_name_error() {
	printf("ERROR (%d): cannot create a board with an empty name.\n", BOARD_EMPTY_NAME_ERROR_CODE);
}

void print_board_create_fail_error() {
	printf("ERROR (%d): board creation failed unexpectedly.\n", BOARD_CREATE_FAIL_ERROR_CODE);
}

void print_user_not_found_error(int id) {
	printf("ERROR (%d): cannot find user with ID %d.\n", USER_NOT_FOUND_ERROR_CODE, id);
}

void print_user_empty_name_error() {
	printf("ERROR (%d): cannot create a user with no name.\n", USER_EMPTY_NAME_ERROR_CODE);
}

void print_user_email_required_error() {
	printf(
		"ERROR (%d): the email of a user is required. Please specify it using a WITH EMAIL clause.\n",
		USER_EMAIL_REQUIRED_ERROR_CODE
	);
}

void print_user_create_fail_error() {
	printf("ERROR (%d): user creation failed unexpectedly.\n", USER_CREATE_FAIL_ERROR_CODE);
}

void print_card_not_found_error(int id) {
	printf("ERROR (%d): cannot find card with ID %d.\n", CARD_NOT_FOUND_ERROR_CODE, id);
}

void print_card_empty_title_error() {
	printf("ERROR (%d): cannot create a card with an empty title.\n", CARD_EMPTY_TITLE_ERROR_CODE);
}

void print_card_create_fail_error() {
	printf("ERROR (%d): card creation failed unexpectedly.\n", CARD_CREATE_FAIL_ERROR_CODE);
}

void print_card_title_too_long_error(int max_length) {
	printf("ERROR (%d): card title exceeds maximum allowed length of %d.\n", CARD_TITLE_TOO_LONG_ERROR_CODE, max_length);
}

void print_card_description_too_long_error(int max_length) {
	printf("ERROR (%d): card description exceeds maximum allowed length of %d.\n", CARD_DESCRIPTION_TOO_LONG_ERROR_CODE, max_length);
}
