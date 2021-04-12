//
// Created by napsu on 4/10/2021.
//

#include "card.h"
#include "user.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int CURRENT_CARD_ID = 0;

card_t *card_create(char *title, char *description){
    card_t *card= (card_t *) malloc(sizeof(card_t));
    if (card == NULL) {
        return NULL;
    }

    if (strlen(title) >= MAX_CARD_TITLE_LENGTH) {
        free(card);
        return NULL;
    }

    if (strlen(description) >= MAX_CARD_DESCRIPTION_LENGTH) {
        free(card);
        return NULL;
    }

    strcpy(card->title, title);
    strcpy(card->description, description);
    card->status = TODO;

    card->id = CURRENT_CARD_ID++;

    return card;
}

bool card_update(card_t *card, char *title, char *description, CARD_STATUS status) {
    if (title != NULL) {
        if (strlen(title) >= MAX_CARD_TITLE_LENGTH) {
            return false;
        }

        strcpy(card->title, title);
    }

    if (description != NULL) {
        if (strlen(description) >= MAX_CARD_DESCRIPTION_LENGTH) {
            return false;
        }

        strcpy(card->description, description);
    }

    card->status = status;

    return true;
}

void card_list_add(card_list_node_t **node, card_t *card) {
    card_list_node_t *new_node = (card_list_node_t *) malloc(sizeof(card_list_node_t));
    new_node->card = card;
    new_node->next = *node;
    *node = new_node;
}

bool card_list_is_empty(card_list_node_t *node) {
    return node == NULL;
}

card_t *card_list_find(card_list_node_t *node, unsigned int id) {
    while (!card_list_is_empty(node)) {
        if (node->card != NULL && node->card->id == id) {
            return node->card;
        }

        node = node->next;
    }

    return NULL;
}

bool card_list_remove(card_list_node_t **node, unsigned int id) {
    card_list_node_t *aux = *node;

    if (aux != NULL && aux->card != NULL && aux->card->id == id) {
        *node = aux->next;
        free(aux);
        return true;
    }

    card_list_node_t *previous;

    while (!card_list_is_empty(aux)) {
        if (aux->card != NULL && aux->card->id == id) {
            previous->next = aux->next;
            free(aux);
            return true;
        }

        previous = aux;
        aux = aux->next;
    }

    return false;
}
