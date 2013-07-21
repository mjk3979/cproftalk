#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "linkedlist.h"

int main(int argc, char **argv)
{
	ll_t list = makeList();
	assert(list.head == NULL);
	
	int val = 7;
	push(&list, &val);
	assert(*(int *)list.head->data == 7);
	assert(list.head->next == NULL);

	assert(*(int *)pop(&list) == 7);
	assert(list.head == NULL);

	int newval = 19;
	push(&list, &val);
	push(&list, &newval);
	assert(*(int *)list.head->data == 19);
	assert(*(int *)list.head->next->data == 7);
	assert(list.head->next->next == NULL);

	assert(*(int *)pop(&list) == 19);
	assert(*(int *)list.head->data == 7);
	assert(list.head->next == NULL);

	assert(*(int *)pop(&list) == 7);
	assert(list.head == NULL);

	int anotherval = 113;
	push(&list, &val);
	push(&list, &newval);
	pushBack(&list, &anotherval);
	assert(*(int *)list.head->data == 19);
	assert(*(int *)list.head->next->data == 7);
	assert(*(int *)list.head->next->next->data == 113);

	assert(*(int *)pop(&list) == 19);
	assert(*(int *)list.head->data == 7);
	assert(*(int *)list.head->next->data == 113);

	assert(*(int *)pop(&list) == 7);
	assert(*(int *)list.head->data == 113);

	assert(*(int *)pop(&list) == 113);
	assert(list.head == NULL);

	puts("All tests passed");

	return 0;
}
