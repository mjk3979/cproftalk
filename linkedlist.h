#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node_t node_t;

struct node_t
{
	void *data;
	node_t *next;
};

typedef struct
{
	node_t *head;
} ll_t;

ll_t makeList();

void push(ll_t *list, void *data);

void *pop(ll_t *list);

#endif
