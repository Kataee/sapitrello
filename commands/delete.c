#include "delete.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_delete(char *parameters) {
	printf("invoked DELETE with parameters: \"%s\"\n", parameters);
	return true;
}
