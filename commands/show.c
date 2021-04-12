#include "show.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_show(char *parameters) {
	printf("invoked SHOW with parameters: \"%s\"\n", parameters);
	return true;
}
