#ifndef PARSER_H
#define PARSER_H

extern const int KEYWORD_TYPE;
extern const int VARIABLE_TYPE;
extern const int LITERAL_TYPE;
extern const int NUM_KEYWORDS;
extern char *KEYWORDS[2];

typedef struct
{
	int type;
	char *name;
	int value;
} token_t;

token_t *parse(FILE *fd, int *size);

#endif
