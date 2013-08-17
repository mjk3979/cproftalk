#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "linkedlist.h"

#define KEYWORD_TYPE	0
#define VARIABLE_TYPE	1
#define LITERAL_TYPE	2
#define LIST_TYPE		3
#define LAMBDA_TYPE		4

#define NUM_KEYWORDS	26

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
#define AND				15
#define OR				16
#define NOT				17

#define BEGIN			18
#define THIS_GUY		19
#define ONE_LESS_CAR	20
#define COME_FROM_BEHIND 21
#define MAP				22
#define FILTER			23
#define CONS			24
#define EMPTY			25

extern char *KEYWORDS[NUM_KEYWORDS];

typedef struct
{
	int type;
	char *name;
	int value;
} token_t;

ll_t parse(FILE *fd, int *size);

#endif
