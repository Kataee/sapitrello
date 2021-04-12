#include "stringutils.h"

#include <string.h>
#include <stdbool.h>

bool is_whitespace(char x) {
	return x == ' ' || x == '\t' || x == '\n';
}

void str_tolowercase(char *input) {
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] >= 'A' && input[i] <= 'Z') {
			input[i] += 0x20;
		}
	}
}

void str_touppercase(char *input) {
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] >= 'a' && input[i] <= 'z') {
			input[i] -= 0x20;
		}
	}
}

void str_trim(char *input) {
	int start_idx = 0;
	int end_idx = strlen(input);

	for (int i = 0; i < strlen(input); i++) {
		if (!is_whitespace(input[i])) {
			break;
		}

		start_idx++;
	}

	if (start_idx == end_idx - 1) {
		return;
	}

	for (int i = strlen(input) - 1; i >= start_idx; i--) {
		if (!is_whitespace(input[i])) {
			break;
		}

		end_idx--;
	}

	if (start_idx == 0 && end_idx == strlen(input)) {
		return;
	}

	for (int i = 0; i < end_idx - start_idx; i++) {
		input[i] = input[start_idx + i];
	}

	input[end_idx - start_idx] = '\0';
}

void str_trim_quotes(char *input) {
	int length = strlen(input);

	if (input[0] != '"' || input[length - 1] != '"') {
		return;
	}

	for (int i = 0; i < length - 2; i++) {
		input[i] = input[i + 1];
	}

	input[length - 2] = '\0';
}
