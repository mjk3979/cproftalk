#ifndef LEXER_H
#define LEXER_H

#include "parser.h"
#include "linkedlist.h"

typedef struct proftalk_expr_t proftalk_expr_t;

struct proftalk_expr_t
{
	int type;
	int value;
	ll_t expressions;
	char *name;
};
	
proftalk_expr_t lex(ll_t *tokens);

#endif
