#include "user.h"

#include <stdlib.h>
#include <string.h>

unsigned int CURRENT_USER_ID = 0;

user_t *user_create(char *name, char *email) {
	user_t *user = (user_t *) malloc(sizeof(user_t));
	if (user == NULL) {
		return NULL;
	}

	user->name = (char *) malloc(strlen(name) * sizeof(char));
	if (user->name == NULL) {
		free(user);
		return NULL;
	}

	user->email = (char *) malloc(strlen(email) * sizeof(char));
	if (user->email == NULL) {
		free(user->name);
		free(user);
		return NULL;
	}

	user->id = CURRENT_USER_ID++;
	strcpy(user->name, name);
	strcpy(user->email, email);

	return user;
}

bool user_update(user_t *user, char *name, char *email) {
	bool ok = true;

	if (name != NULL) {
		user->name = (char *) realloc(user->name, strlen(name) * sizeof(char));
		if (user->name != NULL) {
			strcpy(user->name, name);
		} else {
			ok = false;
		}
	}

	if (email != NULL) {
		user->email = (char *) realloc(user->email, strlen(email) * sizeof(char));
		if (user->email != NULL) {
			strcpy(user->email, email);
		} else {
			ok = false;
		}
	}

	return ok;
}

void user_list_add(user_list_node_t **node, user_t *user) {
	user_list_node_t *new_node = (user_list_node_t *) malloc(sizeof(user_list_node_t));
	new_node->user = user;
	new_node->next = *node;
	*node = new_node;
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
