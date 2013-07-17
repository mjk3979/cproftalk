#include <stdio.h>
#include "parser.h"

int main(int argc, char **argv)
{
	int numtokens;
	token_t *tokens = parse(stdin, &numtokens);
	int i;
	for(i=0; i < numtokens; ++i)
	{
		printf("$token$ type: %d, name: %s, value: %d\n", tokens[i].type, tokens[i].name, tokens[i].value);
	}

	return 0;
}
