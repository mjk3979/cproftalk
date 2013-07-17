#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

const int KEYWORD_TYPE = 0;
const int VARIABLE_TYPE = 1;
const int LITERAL_TYPE = 2;
const int NUM_KEYWORDS = 2;
char *KEYWORDS[2] = {"(", ")"};

static inline token_t getTokenFromString(char *str_token)
{
	token_t token; memset(&token, 0, sizeof(token));
	int i;
	for (i=0; i < NUM_KEYWORDS; ++i)
	{
		if (strcmp(str_token, KEYWORDS[i]) == 0)
		{
			token.type = KEYWORD_TYPE;
			token.value = i;
			free(str_token);
			return token;
		}
	}
	token.type = VARIABLE_TYPE;
	token.name = str_token;
	return token;
}

token_t *parse(FILE *fd, int *size)
{
	int arr_size = 4;
	int num_tokens = 0;
	token_t *tokens = malloc(sizeof(token_t) * arr_size);
	{
		if (num_tokens >= arr_size)
		{
			arr_size <<= 1;
			realloc(tokens, sizeof(token_t) * arr_size);
		}

		tokens[num_tokens] = getTokenFromString(str_token);

		++num_tokens;
	}

	*size = num_tokens;

	// clean up unused memory
	realloc(tokens, sizeof(token_t) * num_tokens);

	return tokens;
}
