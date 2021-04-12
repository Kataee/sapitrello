#ifndef __UTILS_ERRORS_H
#define __UTILS_ERRORS_H

typedef enum ERROR_CODES {
	SYNTAX_ERROR_CODE = 1001,

	BOARD_NOT_FOUND_ERROR_CODE = 1051,
	BOARD_EMPTY_NAME_ERROR_CODE = 1052,
	BOARD_CREATE_FAIL_ERROR_CODE = 1053
} ERROR_CODES;

void print_syntax_error(const char *near);

void print_board_not_found_error(int id);
void print_board_empty_name_error();
void print_board_create_fail_error();

#endif // __UTILS_ERRORS_H
