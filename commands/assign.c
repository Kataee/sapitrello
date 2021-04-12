#include "assign.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_assign(char *parameters) {
	printf("invoked ASSIGN with parameters: \"%s\"\n", parameters);
	return true;
}
