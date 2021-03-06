#ifndef __MODELS_CARD_H
#define __MODELS_CARD_H

#include <stdbool.h>
#include "user.h"

#define MAX_CARD_TITLE_LENGTH 0x100
#define MAX_CARD_DESCRIPTION_LENGTH 0x1000

extern unsigned int CURRENT_CARD_ID;

typedef enum CARD_STATUS {
    TODO,
    DOING,
    DONE
} CARD_STATUS;

typedef struct card {
    unsigned int id;

    char title[MAX_CARD_TITLE_LENGTH];
    char description[MAX_CARD_DESCRIPTION_LENGTH];
    CARD_STATUS status;

    unsigned int assignee_count;
    user_list_node_t *assignees;
} card_t;

typedef struct card_list_node {
    card_t *card;
    struct card_list_node *next;
} card_list_node_t;

card_t *card_create(char *title, char *description);
bool card_update(card_t *card, char *title, char *description, CARD_STATUS status);
void card_list_add(card_list_node_t **node, card_t *card);
void card_list_add_front(card_list_node_t **node, card_t *card);
bool card_list_is_empty(card_list_node_t *node);
card_t *card_list_find(card_list_node_t *node, unsigned int id);
bool card_list_remove(card_list_node_t **node, unsigned int id);
void card_list_clear(card_list_node_t **node);

#endif // __MODELS_CARD_H
