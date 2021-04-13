#ifndef __MODELS_BOARD_H
#define __MODELS_BOARD_H

#include <stdbool.h>

#include "card.h"
#include "user.h"

#define MAX_BOARD_NAME_LENGTH 0x100

typedef struct board {
	unsigned int id;
	char name[MAX_BOARD_NAME_LENGTH];

	unsigned int member_count;
	user_list_node_t *members;

	unsigned int card_count;
	card_list_node_t *cards;
} board_t;

typedef struct board_list_node {
	board_t *board;
	struct board_list_node *next;
} board_list_node_t;

board_t *board_create(char *name);
bool board_update(board_t *board, char *name);

void board_list_add(board_list_node_t **node, board_t *board);
bool board_list_is_empty(board_list_node_t *node);
board_t *board_list_find(board_list_node_t *node, unsigned int id);
bool board_list_remove(board_list_node_t **node, unsigned int id);

#endif // __MODELS_BOARD_H
