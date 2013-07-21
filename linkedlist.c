#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

ll_t makeList()
{
	ll_t newList;
	newList.head = NULL;
	newList.back = NULL;
	return newList;
}

void push(ll_t *list, void *data)
{
	node_t *node = malloc(sizeof(node_t));
	node->data = data;
	node->next = list->head;
	list->head = node;

	if (list->back == NULL)
		list->back = node;
}

void *pop(ll_t *list)
{
	assert(list->head != NULL);

	void *data = list->head->data;
	list->head = list->head->next;

	if (list->head == NULL)
		list->back = NULL;

	return data;
}

void *peek(ll_t *list)
{
	assert(list->head != NULL);
	return list->head->data;
}

void pushBack(ll_t *list, void *data)
{
	node_t *node = malloc(sizeof(node_t));
	node->data = data;
	node->next = NULL;

	if (list->back != NULL)
		list->back->next = node;
	list->back = node;

	if (list->head == NULL)
		list->head = node;
}
