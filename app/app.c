#include "app.h"
#include "database.h"

#include "../models/board.h"
#include "../parser/stql.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

database_t APP_DATABASE;
board_t *ACTIVE_BOARD = NULL;
bool is_running = true;

void start_application() {
	load_database(&APP_DATABASE);

	bool should_run = true;
	char line[0xFF];

	while (is_running) {
		printf("sapitrello> ");
		scanf("%[^\n]", line);
		getchar();

		stql_parse(line);
	}
}

void stop_application() {
	is_running = false;
}
