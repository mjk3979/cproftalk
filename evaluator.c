#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "linkedlist.h"
#include "evaluator.h"

static proftalk_expr_t handleBuiltIn(int function_id, ll_t *args)
{
	switch(function_id)
	{
		case INSOFARAS:
		{
			proftalk_expr_t conditional = eval(*(proftalk_expr_t *)pop(args));
			if (conditional.type != LITERAL_TYPE)
			{
				fputs("Invalid type for conditional.", stderr);
				exit(1);
			}
			if (conditional.value == 0)
			{
				pop(args);
				return eval(*(proftalk_expr_t *)pop(args));
			}
			else
			{
				return eval(*(proftalk_expr_t *)pop(args));
			}
		}
	}
	assert(0);
}

proftalk_expr_t eval(proftalk_expr_t expr)
{
	switch(expr.type)
	{
		case LIST_TYPE:
		{
			proftalk_expr_t function = eval(*(proftalk_expr_t *)pop(&expr.expressions));
			if (function.type == KEYWORD_TYPE)
				return handleBuiltIn(function.value, &expr.expressions);
			break;
		}
		case LITERAL_TYPE:
		case KEYWORD_TYPE:
			return expr;
	}
	assert(0);
}
