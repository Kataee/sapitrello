#include "update.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_update(char *parameters) {
	printf("invoked UPDATE with parameters: \"%s\"\n", parameters);
	return true;
}
