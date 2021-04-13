#include "user.h"

#include <stdlib.h>
#include <string.h>

unsigned int CURRENT_USER_ID = 0;

user_t *user_create(char *name, char *email) {
	user_t *user = (user_t *) malloc(sizeof(user_t));
	if (user == NULL) {
		return NULL;
	}

	if (strlen(name) >= MAX_USER_NAME_LENGTH) {
		free(user);
		return NULL;
	}

	if (strlen(email) >= MAX_USER_EMAIL_LENGTH) {
		free(user);
		return NULL;
	}

	user->id = CURRENT_USER_ID++;
	strcpy(user->name, name);
	strcpy(user->email, email);

	return user;
}

bool user_update(user_t *user, char *name, char *email) {
	if (name != NULL) {
		if (strlen(name) >= MAX_USER_NAME_LENGTH) {
			return false;
		}

		strcpy(user->name, name);
	}

	if (email != NULL) {
		if (strlen(email) >= MAX_USER_EMAIL_LENGTH) {
			return false;
		}

		strcpy(user->email, email);
	}
}

void user_list_add(user_list_node_t **node, user_t *user) {
	user_list_node_t *new_node = (user_list_node_t *) malloc(sizeof(user_list_node_t));
	new_node->user = user;
	new_node->next = *node;
	*node = new_node;
}

void user_list_add_front(user_list_node_t **node, user_t *user) {
    user_list_node_t *new_node = (user_list_node_t *) malloc(sizeof(user_list_node_t));
    user_list_node_t *last = *node;

    new_node->user = user;
    new_node->next = NULL;

    if (*node == NULL) {
        *node = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

bool user_list_is_empty(user_list_node_t *node) {
	return node == NULL;
}

user_t *user_list_find(user_list_node_t *node, unsigned int id) {
	while (!user_list_is_empty(node)) {
		if (node->user != NULL && node->user->id == id) {
			return node->user;
		}

		node = node->next;
	}

	return NULL;
}

bool user_list_remove(user_list_node_t **node, unsigned int id) {
	user_list_node_t *aux = *node;

	if (aux != NULL && aux->user != NULL && aux->user->id == id) {
		*node = aux->next;
		free(aux);
		return true;
	}

	user_list_node_t *previous;

	while (!user_list_is_empty(aux)) {
		if (aux->user != NULL && aux->user->id == id) {
			previous->next = aux->next;
			free(aux);
			return true;
		}

		previous = aux;
		aux = aux->next;
	}

	return false;
}

void user_list_clear(user_list_node_t **node) {
	user_list_node_t *aux = *node;
	user_list_node_t *next;

	while (aux != NULL) {
		next = aux->next;
		free(aux);
		aux = next;
	}

	*node = NULL;
}
