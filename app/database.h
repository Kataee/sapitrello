#ifndef __APP_DATABASE_H
#define __APP_DATABASE_H

#include "../models/board.h"
#include "../models/card.h"
#include "../models/user.h"

extern const unsigned char MAGIC_NUMBER;

typedef struct database {
	unsigned long user_count;
	unsigned long board_count;
	unsigned long card_count;

	user_list_node_t *users;
	board_list_node_t *boards;
	card_list_node_t *cards;
} database_t;

void load_database(database_t *database);
void save_database(database_t *database);

#endif // __APP_DATABASE_H
