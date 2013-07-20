#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

const int KEYWORD_TYPE = 0;
const int VARIABLE_TYPE = 1;
const int LITERAL_TYPE = 2;
const int NUM_KEYWORDS = 5;

char *KEYWORDS[5] = {"(", ")", "insofaras", "bring-me-back-something-good", "yknow"};
const int LEFT_PAREN = 0;
const int RIGHT_PAREN = 1;
const int INSOFARAS = 2;
const int BRING_ME_BACK_SOMETHING_GOOD = 3;
const int YKNOW = 4;

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
	++buffer;
	while (!isWhiteSpace(*buffer) && *buffer != '(' && *buffer != ')' && *buffer != '\0')
	{
		++actual_size;
		if (actual_size >= buffer_size)
		{
			buffer_size <<= 1;
			realloc(retval, buffer_size);
		}
		retval[actual_size-2] = *buffer;
		++buffer;
	}
	
	retval[actual_size-1] = '\0';
	*buffer_ptr = buffer;
	return retval;
}

token_t *parse(FILE *fd, int *size)
{
	int arr_size = 4;
	int num_tokens = 0;
	token_t *tokens = malloc(sizeof(token_t) * arr_size);
	char *str_token = NULL;
	char *line = NULL;
	int cont = 1;
	int linesize;
	while(cont)
	{
		if (getline(&line, &linesize, fd) == -1)
			cont = 0;
		else
		{
			// So we can still free line later
			char *line_it = line;
			while ((str_token = getNextString(&line_it)) != NULL)
			{
				puts(str_token);
				if (num_tokens >= arr_size)
				{
					arr_size <<= 1;
					realloc(tokens, sizeof(token_t) * arr_size);
				}

				tokens[num_tokens] = getTokenFromString(str_token);

				++num_tokens;
			}
		}
	}
	free(line);

	*size = num_tokens;

	// clean up unused memory
	realloc(tokens, sizeof(token_t) * num_tokens);

	return tokens;
}
