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
	global_env = makeEnv(NULL);
	int result = eval(expr, &global_env).value;
	printf("%d\n", result);
	
	return 0;
}
