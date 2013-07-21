#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

ll_t makeList()
{
	ll_t newList;
	newList.head = NULL;
	return newList;
}

void push(ll_t *list, void *data)
{
	node_t *node = malloc(sizeof(node_t));
	node->data = data;
	node->next = list->head;
	list->head = node;
}

void *pop(ll_t *list)
{
	assert(list->head != NULL);

	void *data = list->head->data;
	list->head = list->head->next;

	return data;
}
