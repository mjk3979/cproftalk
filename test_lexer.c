#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"
#include "parser.h"
#include "lexer.h"

int main(int argc, char **argv)
{
	ll_t tokens = makeList();
	token_t *temps = malloc(sizeof(token_t) * 10);
		
	temps[0].type = KEYWORD_TYPE;
	temps[0].value = LEFT_PAREN;

	temps[1].type = LITERAL_TYPE;
	temps[1].value = 157;

	push(&tokens, &temps[1]);
	proftalk_expr_t expr = lex(&tokens);

	assert(expr.type == LITERAL_TYPE && expr.value == 157);

	temps[2].type = LITERAL_TYPE;
	temps[2].value = 10067;
	
	temps[3].type = KEYWORD_TYPE;
	temps[3].value = RIGHT_PAREN;

	pushBack(&tokens, &temps[0]);
	pushBack(&tokens, &temps[1]);
	pushBack(&tokens, &temps[0]);
	pushBack(&tokens, &temps[2]);
	pushBack(&tokens, &temps[1]);
	pushBack(&tokens, &temps[3]);
	pushBack(&tokens, &temps[3]);

	expr = lex(&tokens);

	assert(expr.type == LIST_TYPE);
	proftalk_expr_t subexpr = *(proftalk_expr_t *)(expr.expressions.head->data);
	assert(subexpr.type == LITERAL_TYPE && subexpr.value == 157);

	subexpr = *(proftalk_expr_t *)(expr.expressions.head->next->data);
	assert(subexpr.type == LIST_TYPE);

	subexpr = *(proftalk_expr_t *)(subexpr.expressions.head->data);
	assert(subexpr.type == LITERAL_TYPE && subexpr.value == 10067);

	puts("All tests passed");

	return 0;
}
