#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "parser.h"
#include "linkedlist.h"

char *KEYWORDS[NUM_KEYWORDS] = {"(", ")", "insofaras", "bring-me-back-something-good", "yknow", "+", "-", "*", "/", "%", "=", "<", ">", "<=", ">=", "and", "or", "not", "begin", "this-guy", "one-less-car", "come-from-behind", "map", "filter", "cons", "empty?", "print"};

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
	int val;
	char *checker = NULL;
	val = strtol(str_token, &checker, 10);
	if (*checker != '\0')
	{
		token.type = VARIABLE_TYPE;
		token.name = str_token;
	}
	else
	{
		token.type = LITERAL_TYPE;
		token.value = val;
		free(str_token);
	}
	return token;
}

static inline int isWhiteSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

static char *getNextString(char **buffer_ptr)
{
	char *buffer = *buffer_ptr;
	while (isWhiteSpace(*buffer))
		++buffer;
	if (*buffer == '\0')
		return NULL;
	int buffer_size = 2;

	// For the first character and the null char at end
	int actual_size = 2;
	char *retval = malloc(sizeof(char) * buffer_size);
	retval[0] = buffer[0];
	if (*buffer != '(' && *buffer != ')')
	{
		++buffer;
		while (!isWhiteSpace(*buffer) && *buffer != '(' && *buffer != ')' && *buffer != '\0')
		{
			++actual_size;
			if (actual_size >= buffer_size)
			{
				buffer_size <<= 1;
				retval = realloc(retval, buffer_size);
			}
			retval[actual_size-2] = *buffer;
			++buffer;
		}
	}
	else
		++buffer;
	
	retval[actual_size-1] = '\0';
	*buffer_ptr = buffer;
	return retval;
}

ll_t parse(FILE *fd, int *size)
{
	token_t *token = NULL;
	int arr_size = 4;
	int num_tokens = 0;
	ll_t tokens = makeList();
	char *str_token = NULL;
	char *line = NULL;
	int cont = 1;
	size_t linesize;
	int line_number = 0;
	while(cont)
	{
		++line_number;
		if (getline(&line, &linesize, fd) == -1)
			cont = 0;
		else
		{
			// So we can still free line later
			char *line_it = line;
			while ((str_token = getNextString(&line_it)) != NULL)
			{
				token = malloc(sizeof(token_t));
				*token = getTokenFromString(str_token);
				token->line_number = line_number;
				pushBack(&tokens, token);

				++num_tokens;
			}
		}
	}
	free(line);

	*size = num_tokens;

	return tokens;
}
