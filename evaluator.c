#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "linkedlist.h"
#include "evaluator.h"
#include "env.h"

static proftalk_expr_t handleUniary(int function_id, ll_t *args, env_t *env)
{
	proftalk_expr_t arg = eval(*(proftalk_expr_t *)pop(args), env);
	proftalk_expr_t retval;
	retval.type = LITERAL_TYPE;

	if (arg.type != LITERAL_TYPE)
	{
		fputs("Invalid first arg to arithmetic operation", stderr);
		exit(1);
	}

	switch (function_id)
	{
		case NOT:
			retval.value = !arg.value;
			break;
	}
	return retval;
}

static proftalk_expr_t handleBinary(int function_id, ll_t *args, env_t *env)
{
	proftalk_expr_t arg1 = eval(*(proftalk_expr_t *)pop(args), env);
	proftalk_expr_t arg2 = eval(*(proftalk_expr_t *)pop(args), env);

	proftalk_expr_t retval;
	retval.type = LITERAL_TYPE;

	if (arg1.type != LITERAL_TYPE)
	{
		fputs("Invalid first arg to arithmetic operation", stderr);
		exit(1);
	}
	if (arg2.type != LITERAL_TYPE)
	{
		fputs("Invalid second arg to arithmetic operation", stderr);
		exit(1);
	}
	switch(function_id)
	{
		case PLUS:
			retval.value = arg1.value + arg2.value;
			break;
		case MINUS:
			retval.value = arg1.value - arg2.value;
			break;
		case MULTIPLY:
			retval.value = arg1.value * arg2.value;
			break;
		case DIVIDE:
			retval.value = arg1.value / arg2.value;
			break;
		case MOD:
			retval.value = arg1.value % arg2.value;
			break;
		case EQUALS:
			retval.value = arg1.value == arg2.value;
			break;
		case LESS_THAN:
			retval.value = arg1.value < arg2.value;
			break;
		case GREATER_THAN:
			retval.value = arg1.value > arg2.value;
			break;
		case LESS_THAN_EQUAL:
			retval.value = arg1.value <= arg2.value;
			break;
		case GREATER_THAN_EQUAL:
			retval.value = arg1.value >= arg2.value;
			break;
		case AND:
			retval.value = arg1.value && arg2.value;
			break;
		case OR:
			retval.value = arg1.value || arg2.value;
			break;
	}
	return retval;
}

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
		case YKNOW:
		{
			proftalk_expr_t name_expr = *(proftalk_expr_t *)pop(args);
			if (name_expr.type != VARIABLE_TYPE)
			{
				fputs("Invalid name for yknow", stderr);
				exit(1);
			}
			proftalk_expr_t value = eval(*(proftalk_expr_t *)pop(args), env);
			env_insert(&global_env, name_expr.name, value);
			return;
		}
		case BEGIN:
		{
			proftalk_expr_t retval;
			while (args->head != NULL)
			{
				retval = eval(*(proftalk_expr_t *)pop(args), env);
			}
			return retval;
		}
		case THIS_GUY:
			return *(proftalk_expr_t *)pop(args);
		case PLUS:
		case MINUS:
		case MULTIPLY:
		case DIVIDE:
		case MOD:
		case EQUALS:
		case LESS_THAN:
		case GREATER_THAN:
		case LESS_THAN_EQUAL:
		case GREATER_THAN_EQUAL:
		case AND:
		case OR:
			return handleBinary(function_id, args, env);
		case NOT:
			return handleUniary(function_id, args, env);

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
		proftalk_expr_t argExpr = eval(*(proftalk_expr_t *)pop(args), env);
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
