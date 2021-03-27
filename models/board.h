#ifndef __MODELS_BOARD_H
#define __MODELS_BOARD_H

#include <stdbool.h>

#include "card.h"
#include "user.h"

extern int CURRENT_BOARD_ID = 0;

typedef struct board {
	unsigned int id;
	char *name;

	user_list_node_t *members;

	unsigned int card_count;
	card_list_node_t *cards;
} board_t;

typedef struct board_list_node {
	board_t *board;
	struct board_list_node *next;
} board_list_node_t;

board_t *board_create(char *name);
void board_update(board_t *board, char *name);

board_list_node *new_board_list();
void board_list_add(board_list_node_t **node, board_t *board);
bool board_list_is_empty(board_list_node_t *node);
board_t *board_list_find(board_list_node_t *node, unsigned int id);
void board_list_remove(board_list_node_t *node, unsigned int id);

#endif // __MODELS_BOARD_H
