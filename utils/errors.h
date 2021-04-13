#ifndef __UTILS_ERRORS_H
#define __UTILS_ERRORS_H

typedef enum ERROR_CODES {
	SYNTAX_ERROR_CODE = 1001,
	MALLOC_ERROR_CODE = 1002,
	ACTIVE_BOARD_NOT_SELECTED_ERROR_CODE = 1003,

	BOARD_NOT_FOUND_ERROR_CODE = 1051,
	BOARD_EMPTY_NAME_ERROR_CODE = 1052,
	BOARD_CREATE_FAIL_ERROR_CODE = 1053,

	USER_NOT_FOUND_ERROR_CODE = 1061,
	USER_EMPTY_NAME_ERROR_CODE = 1062,
	USER_EMAIL_REQUIRED_ERROR_CODE = 1063,
	USER_CREATE_FAIL_ERROR_CODE = 1064,

	CARD_NOT_FOUND_ERROR_CODE = 1071,
	CARD_EMPTY_TITLE_ERROR_CODE = 1072,
	CARD_CREATE_FAIL_ERROR_CODE = 1073,
	CARD_TITLE_TOO_LONG_ERROR_CODE = 1074,
	CARD_DESCRIPTION_TOO_LONG_ERROR_CODE = 1075
} ERROR_CODES;

void print_syntax_error(const char *near);
void print_malloc_error(const char *during);
void print_active_board_not_selected_error();

void print_board_not_found_error(int id);
void print_board_empty_name_error();
void print_board_create_fail_error();

void print_user_not_found_error(int id);
void print_user_empty_name_error();
void print_user_email_required_error();
void print_user_create_fail_error();

void print_card_not_found_error(int id);
void print_card_empty_title_error();
void print_card_create_fail_error();
void print_card_title_too_long_error(int max_length);
void print_card_description_too_long_error(int max_length);

#endif // __UTILS_ERRORS_H
