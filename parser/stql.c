#include "stql.h"

#include "../commands/add.h"
#include "../commands/assign.h"
#include "../commands/create.h"
#include "../commands/delete.h"
#include "../commands/describe.h"
#include "../commands/exit.h"
#include "../commands/save.h"
#include "../commands/select.h"
#include "../commands/show.h"
#include "../commands/update.h"
#include "../commands/use.h"

#include "../utils/commandutils.h"
#include "../utils/errors.h"
#include "../utils/stringutils.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool stql_parse_single(char *statement) {
	char command[10];
	char *parameters;

	sscanf(statement, "%s", command);
	str_tolowercase(command);

	if (strcmp(command, "save") == 0) {
		cmd_save();
		return true;
	}

	if (strcmp(command, "exit") == 0) {
		cmd_exit();
		return true;
	}

	get_command_parameters(command, statement, &parameters);

	if (strcmp(command, "create") == 0) {
		return cmd_create(parameters);
	}

	if (strcmp(command, "show") == 0) {
		return cmd_show(parameters);
	}

	if (strcmp(command, "use") == 0) {
		return cmd_use(parameters);
	}

	if (strcmp(command, "add") == 0) {
		return cmd_add(parameters);
	}

	if (strcmp(command, "assign") == 0) {
		return cmd_assign(parameters);
	}

	if (strcmp(command, "describe") == 0) {
		return cmd_describe(parameters);
	}

	if (strcmp(command, "select") == 0) {
		return cmd_select(parameters);
	}

	if (strcmp(command, "update") == 0) {
		return cmd_update(parameters);
	}

	if (strcmp(command, "delete") == 0) {
		return cmd_delete(parameters);
	}

	print_syntax_error(command);
	return false;
}

bool stql_parse(char *input) {
	char *statement = strtok(input, ";");

	while (statement != NULL) {
		str_trim(statement);

		if (!stql_parse_single(statement)) {
			return false;
		}

		statement = strtok(NULL, ";");
	}

	return true;
}
