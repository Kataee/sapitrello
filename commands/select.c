#include "select.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_select(char *parameters) {
	printf("invoked SELECT with parameters: \"%s\"\n", parameters);
	return true;
}
