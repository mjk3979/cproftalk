#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "linkedlist.h"

#define KEYWORD_TYPE	0
#define VARIABLE_TYPE	1
#define LITERAL_TYPE	2
#define LIST_TYPE		3
#define LAMBDA_TYPE		4

#define NUM_KEYWORDS	15

#define LEFT_PAREN		0
#define RIGHT_PAREN		1
#define INSOFARAS		2
#define BRING_ME_BACK_SOMETHING_GOOD	3
#define YKNOW			4

#define PLUS			5
#define MINUS			6
#define MULTIPLY		7
#define DIVIDE			8
#define MOD				9
#define EQUALS			10
#define LESS_THAN		11
#define GREATER_THAN	12
#define LESS_THAN_EQUAL	13
#define GREATER_THAN_EQUAL	14

extern char *KEYWORDS[15];

typedef struct
{
	int type;
	char *name;
	int value;
} token_t;

ll_t parse(FILE *fd, int *size);

#endif
