#ifndef LIST_H
#define LIST_H

#include <sys/types.h>

/**
 * struct list_t - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_t
{
	int num;
	char *str;
	struct list_t *next;
} list_t;

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

list_t *node_starts_with(list_t *node, char *prefix, char c);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
ssize_t get_node_index(list_t *head, const list_t *node);

#endif
