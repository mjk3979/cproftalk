#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "linkedlist.h"
#include "evaluator.h"
#include "env.h"

static proftalk_expr_t handleBuiltIn(int function_id, ll_t *args, env_t *env)
{
	switch(function_id)
	{
		case INSOFARAS:
		{
			proftalk_expr_t conditional = eval(*(proftalk_expr_t *)pop(args), env);
			if (conditional.type != LITERAL_TYPE)
			{
				fputs("Invalid type for conditional.", stderr);
				exit(1);
			}
			if (conditional.value == 0)
			{
				pop(args);
				return eval(*(proftalk_expr_t *)pop(args), env);
			}
			else
			{
				return eval(*(proftalk_expr_t *)pop(args), env);
			}
		}
		case BRING_ME_BACK_SOMETHING_GOOD:
		{
			proftalk_expr_t retval;
			retval.type = LAMBDA_TYPE;
			retval.expressions = *args;
			return retval;
		}
		case PLUS:
		{
			proftalk_expr_t arg1 = eval(*(proftalk_expr_t *)pop(args), env);
			proftalk_expr_t arg2 = eval(*(proftalk_expr_t *)pop(args), env);
			if (arg1.type != LITERAL_TYPE)
			{
				fputs("Invalid first arg to addition", stderr);
				exit(1);
			}
			if (arg2.type != LITERAL_TYPE)
			{
				fputs("Invalid second arg to addition", stderr);
				exit(1);
			}
			arg1.value += arg2.value;
			return arg1;
		}

	}
	assert(0);
}

static proftalk_expr_t evalLambda(proftalk_expr_t lambda, ll_t *args, env_t *env)
{
	proftalk_expr_t paramList = *(proftalk_expr_t *)pop(&lambda.expressions);
	ll_t params = paramList.expressions;
	while (params.head != NULL)
	{
		proftalk_expr_t paramExpr = *(proftalk_expr_t *)pop(&params);
		if (paramExpr.type != VARIABLE_TYPE)
		{
			fputs("Invalid parameter list.", stderr);
			exit(1);
		}
		proftalk_expr_t argExpr = *(proftalk_expr_t *)pop(args);
		env_insert(env, paramExpr.name, argExpr);
	}
	proftalk_expr_t toEval = *(proftalk_expr_t *)pop(&lambda.expressions);
	return eval(toEval, env);
}

proftalk_expr_t eval(proftalk_expr_t expr, env_t *parent_env)
{
	env_t env = makeEnv(parent_env);
	switch(expr.type)
	{
		case LIST_TYPE:
		{
			proftalk_expr_t function = eval(*(proftalk_expr_t *)pop(&expr.expressions), &env);
			switch(function.type)
			{
				case KEYWORD_TYPE:
					return handleBuiltIn(function.value, &expr.expressions, &env);
				case LAMBDA_TYPE:
					return evalLambda(function, &expr.expressions, &env);
			}
			assert(0);
			break;
		}
		case LITERAL_TYPE:
		case KEYWORD_TYPE:
			return expr;
		case VARIABLE_TYPE:
		{
			proftalk_expr_t retval;
			int success = env_find(&env, expr.name, &retval);
			if (!success)
			{
				fprintf(stderr, "Unbound variable %s", expr.name);
				exit(1);
			}
			return retval;
		}
	}
	assert(0);
}
