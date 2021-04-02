#ifndef __MODELS_USER_H
#define __MODELS_USER_H

#include <stdbool.h>

typedef struct user {
	unsigned int id;
	char *name;
	char *email;
} user_t;

typedef struct user_list_node {
	user_t *user;
	struct user_list_node *next;
} user_list_node_t;

user_t *user_create(char *name, char *email);
void user_update(user_t *user, char *name, char *email);

user_list_node_t *new_user_list();
void user_list_add(user_list_node_t **node, user_t *user);
bool user_list_is_empty(user_list_node_t *node);
user_t *user_list_find(user_list_node_t *node, unsigned int id);
void user_list_remove(user_list_node_t *node, unsigned int id);

#endif // __MODELS_USER_H
