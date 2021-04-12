#include "use.h"

#include <stdbool.h>
#include <stdio.h>

bool cmd_use(char *parameters) {
	printf("invoked USE with parameters: \"%s\"\n", parameters);
	return true;
}
