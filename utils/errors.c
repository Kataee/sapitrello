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

void print_board_not_found_error(int id) {
	printf("ERROR (%d): cannot find board with ID %d.\n", BOARD_NOT_FOUND_ERROR_CODE, id);
}

void print_board_empty_name_error() {
	printf("ERROR (%d): cannot create a board with an empty name.\n", BOARD_EMPTY_NAME_ERROR_CODE);
}

void print_board_create_fail_error() {
	printf("ERROR (%d): board creation failed unexpectedly.\n", BOARD_CREATE_FAIL_ERROR_CODE);
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
