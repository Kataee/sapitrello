#include "commandutils.h"
#include "stringutils.h"

#include <stdlib.h>
#include <string.h>

void get_command_parameters(char *command, char *statement, char **target) {
	int length = strlen(statement) - strlen(command) + 1;

	*target = (char *) malloc(length * sizeof(char));
	if (*target == NULL) {
		return;
	}

	memcpy(*target, statement + strlen(command), length);
	str_trim(*target);
}
