#include "save.h"

#include "../app/app.h"
#include "../app/database.h"

void cmd_save() {
	save_database(APP_DATABASE);
}
