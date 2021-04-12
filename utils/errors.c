#include "errors.h"

#include <stdio.h>

void print_syntax_error(const char *near) {
	printf("ERROR (%d): syntax error near '%s'.\n", SYNTAX_ERROR_CODE, near);
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
