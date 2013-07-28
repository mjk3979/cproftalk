#include <assert.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "evaluator.h"

int main(int argc, char **argv)
{
	int tokenCount;
	ll_t tokens = parse(stdin, &tokenCount);
	proftalk_expr_t expr = lex(&tokens);
	env_t global = makeEnv(NULL);
	int result = eval(expr, &global).value;
	printf("%d", result);
	
	return 0;
}
