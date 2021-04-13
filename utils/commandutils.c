#include "commandutils.h"
#include "stringutils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int __extract_parameter_with_quotes(char *source, char **destination) {
	char *current = (char *) malloc(strlen(source) * sizeof(char));
	if (current == NULL) {
		return -1;
	}

	*destination = (char *) malloc(strlen(source) * sizeof(char));
	if (*destination == NULL) {
		return -1;
	}

	int current_length;
	int total_length = 0;

	sscanf(source, "%s%n", current, &current_length);
	source += current_length;
	total_length += current_length;

	strcpy(*destination, current);

	if (current[0] != '"' || (current[0] == '"' && current[strlen(current) - 1] == '"')) {
		return current_length;
	}

	while (sscanf(source, "%s%n", current, &current_length) == 1) {
		strcat(*destination, " ");
		strcat(*destination, current);

		source += current_length;
		total_length += current_length;

		if (current[strlen(current) - 1] == '"') {
			return total_length;
		}
	}

	return -1;
}

void get_command_parameters(char *command, char *statement, char **target) {
	int length = strlen(statement) - strlen(command) + 1;

	*target = (char *) malloc(length * sizeof(char));
	if (*target == NULL) {
		return;
	}

	memcpy(*target, statement + strlen(command), length);
	str_trim(*target);
}

int extract_parameter(char **source, char **destination) {
	int chars_read = __extract_parameter_with_quotes(*source, destination);
	if (chars_read == -1) {
		return chars_read;
	}

	*source += chars_read;

	// TODO: trimming could be optimized.
	str_trim_quotes(*destination);
	str_trim(*destination);

	return chars_read;
}
