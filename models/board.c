#include "board.h"
#include "user.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

unsigned int CURRENT_BOARD_ID = 0;

board_t *board_create(char *name) {
    board_t *board = (board_t *) malloc(sizeof(board_t));

    if (board == NULL) {
        return NULL;
    }

    board->card_count = 0;
    board->cards = NULL;
    board->member_count = 0;
    board->members = NULL;

    if (strlen(name) >= MAX_BOARD_NAME_LENGTH) {
        free(board);
        return NULL;
    }

    strcpy(board->name, name);

    board->id = CURRENT_BOARD_ID++;

    return board;
}


bool board_update(board_t *board, char *name) {
    if (name != NULL) {
        if (strlen(name) >= MAX_BOARD_NAME_LENGTH) {
            return false;
        }

        strcpy(board->name, name);
    }

    return true;
}


void board_list_add(board_list_node_t **node, board_t *board) {
    board_list_node_t *new_node = (board_list_node_t *) malloc (sizeof(board_list_node_t));
    new_node->board = board;
    new_node->next = *node;
    *node = new_node;
}


bool board_list_is_empty(board_list_node_t *node) {
    return node == NULL;
}


board_t *board_list_find(board_list_node_t *node, unsigned int id) {
    while (!board_list_is_empty(node)) {
        if (node->board != NULL && node->board->id == id) {
            return node->board;
        }

        node = node->next;
    }
    return NULL;
}


bool board_list_remove(board_list_node_t **node, unsigned int id) {
    board_list_node_t *aux = *node;

    if (aux != NULL && aux->board != NULL && aux->board->id == id) {
        *node = aux->next;
        free(aux);
        return true;
    }

    board_list_node_t *previous;

    while (!board_list_is_empty(aux)) {
        if (aux->board != NULL && aux->board->id == id) {
                previous->next = aux->next;
                card_list_clear(&(aux->board->cards));
                free(aux);
                return true;
        }

        previous = aux;
        aux = aux->next;
    }
    return false;
}
