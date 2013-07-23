#include <stdio.h>
#include "parser.h"
#include "linkedlist.h"

int main(int argc, char **argv)
{
	int numtokens;
	ll_t tokens = parse(stdin, &numtokens);
	int i;
	for(i=0; i < numtokens; ++i)
	{
		token_t token = *(token_t *)pop(&tokens);
		printf("$token$ type: %d, name: %s, value: %d\n", token.type, token.name, token.value);
	}

	return 0;
}
