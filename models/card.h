#ifndef __MODELS_CARD_H
#define __MODELS_CARD_H

#include <stdbool.h>

#include "user.h"

typedef enum CARD_STATUS {
	TODO,
	DOING,
	DONE
} CARD_STATUS;

typedef struct card {
	unsigned int id;
	char *title;
	char *description;
	CARD_STATUS status;

	user_list_node_t *assignees;
} card_t;

typedef struct card_list_node {
	card_t *card;
	struct card_list_node *next;
} card_list_node_t;

card_t *card_create(char *name, char *description);
void card_update(card_t *card, char *name, char *description, CARD_STATUS status);

void card_list_add(card_list_node_t **node, card_t *card);
bool card_list_is_empty(card_list_node_t *node);
card_t *card_list_find(card_list_node_t *node, unsigned int id);
void card_list_remove(card_list_node_t **node, unsigned int id);

#endif // __MODELS_CARD_H
