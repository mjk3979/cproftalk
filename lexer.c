#include <stdlib.h>
#include "parser.h"
#include "lexer.h"

proftalk_expr_t lex(ll_t *tokens)
{
	proftalk_expr_t retval;
	
	// Get the token
	token_t token = *(token_t *)pop(tokens);
	
	if (token.type == KEYWORD_TYPE && token.value == LEFT_PAREN)
	{
		retval.type = LIST_TYPE;
		retval.expressions = makeList();
		while (!(token.type == KEYWORD_TYPE && token.value == RIGHT_PAREN))
		{
			proftalk_expr_t *ele = malloc(sizeof(proftalk_expr_t));
			*ele = lex(tokens);
			pushBack(&retval.expressions, ele);
			token = *(token_t *)peek(tokens);
		}
		pop(tokens);
		return retval;
	}
	else
	{
		retval.type = token.type;
		retval.value = token.value;
		retval.name = token.name;
		return retval;
	}
}
