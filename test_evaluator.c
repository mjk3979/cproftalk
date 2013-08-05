#include <assert.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "evaluator.h"

static void print_expr(proftalk_expr_t expr)
{
	if (expr.type == LIST_TYPE)
	{
		printf("( ");

		while(expr.expressions.head != NULL)
			print_expr(*(proftalk_expr_t *)pop(&expr.expressions));
		printf(") ");
	}
	else
	{
		printf("%d ", expr.value);
	}
}

int main(int argc, char **argv)
{
	int tokenCount;
	ll_t tokens = parse(stdin, &tokenCount);
	proftalk_expr_t expr = lex(&tokens);
	global_env = makeEnv(NULL);
	print_expr(eval(expr, &global_env));
	
	return 0;
}
