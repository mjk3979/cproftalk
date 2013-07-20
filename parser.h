#ifndef PARSER_H
#define PARSER_H

extern const int KEYWORD_TYPE;
extern const int VARIABLE_TYPE;
extern const int LITERAL_TYPE;
extern const int NUM_KEYWORDS;

extern char *KEYWORDS[5];
extern const int LEFT_PAREN;
extern const int RIGHT_PAREN;
extern const int INSOFARAS;
extern const int BRING_ME_BACK_SOMETHING_GOOD;
extern const int YKNOW;

typedef struct
{
	int type;
	char *name;
	int value;
} token_t;

token_t *parse(FILE *fd, int *size);

#endif
