#include "exit.h"

#include "../app/app.h"

#include <stdio.h>

void cmd_exit() {
	printf("Bye.\n");
	stop_application();
}
