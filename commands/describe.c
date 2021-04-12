#include "describe.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_describe(char *parameters) {
	printf("invoked DESCRIBE with parameters: \"%s\"\n", parameters);
	return true;
}
