#ifndef __APP_H
#define __APP_H

#define APP_VERSION "0.1.0"

#include "database.h"

#include "../models/board.h"

extern database_t *APP_DATABASE;
extern board_t *ACTIVE_BOARD;

void start_application(int argc, char **argv);
void stop_application();

#endif // __APP_H
