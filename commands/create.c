#include "create.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_create(char *parameters) {
	printf("invoked CREATE with parameters: \"%s\"\n", parameters);
	return true;
}
