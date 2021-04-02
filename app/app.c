#include "app.h"

#include "database.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

database_t APP_DATABASE;
bool is_running = true;

void start_application() {
	load_database(&APP_DATABASE);

	bool should_run = true;
	char command[0xFF];

	while (is_running) {
		printf("sapitrello> ");
		scanf("%s", command); // TODO

		// parse(command);

		// temporary
		if (strcmp(command, "exit") == 0) {
			stop_application();
			continue;
		}

		if (strcmp(command, "save") == 0) {
			save_database(&APP_DATABASE);
			continue;
		}
	}
}

void stop_application() {
	is_running = false;
}
