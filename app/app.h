#ifndef __APP_H
#define __APP_H

#include "database.h"

#include "../models/board.h"

extern database_t APP_DATABASE;
extern board_t *ACTIVE_BOARD;

void start_application();
void stop_application();

#endif // __APP_H
