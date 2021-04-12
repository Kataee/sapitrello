#include "add.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_add(char *parameters) {
	printf("invoked ADD with parameters: \"%s\"\n", parameters);
	return true;
}
