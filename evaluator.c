#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "linkedlist.h"
#include "evaluator.h"
#include "env.h"

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

static proftalk_expr_t handleUniary(int function_id, ll_t *args, env_t *env)
{
	proftalk_expr_t arg = eval(*(proftalk_expr_t *)pop(args), env);
	proftalk_expr_t retval;
	retval.type = LITERAL_TYPE;

	if (arg.type != LITERAL_TYPE)
	{
		fprintf(stderr, "Invalid first arg to arithmetic operation\n\tOperation: %s\n", KEYWORDS[function_id]);
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

static proftalk_expr_t handleBinary(int function_id, ll_t *args, env_t *env, int line_number)
{
	proftalk_expr_t arg1 = eval(*(proftalk_expr_t *)pop(args), env);
	proftalk_expr_t arg2 = eval(*(proftalk_expr_t *)pop(args), env);

	proftalk_expr_t retval;
	retval.type = LITERAL_TYPE;

	if (arg1.type != LITERAL_TYPE)
	{
		fprintf(stderr, "Invalid first arg to arithmetic operation\n\tOperation: %s\n\tType: %d\n\tName: %s\nLine number: %d\n", KEYWORDS[function_id], arg1.type, arg1.name, line_number);
		exit(1);
	}
	if (arg2.type != LITERAL_TYPE)
	{
		fprintf(stderr, "Invalid second arg to arithmetic operation\n\tOperation: %s\n\n\tType: %d\nLine number: %d\n", KEYWORDS[function_id], arg2.type, line_number);
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

static proftalk_expr_t handleBuiltIn(int function_id, ll_t *args, env_t *env, int line_number, env_t *parent_env)
{
	switch(function_id)
	{
		case INSOFARAS:
		{
			proftalk_expr_t conditional = eval(*(proftalk_expr_t *)pop(args), env);
			if (conditional.type != LITERAL_TYPE)
			{
				fprintf(stderr, "Invalid type for conditional.\nLine number: %d\n", line_number);
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
				fprintf(stderr, "Invalid name for yknow\nLine number: %d\n", line_number);
				exit(1);
			}
			proftalk_expr_t value = eval(*(proftalk_expr_t *)pop(args), env);
			env_insert(parent_env, name_expr.name, value);
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
		case ONE_LESS_CAR:
		{
			proftalk_expr_t list = eval(*(proftalk_expr_t *)pop(args), env);
			if (list.type != LIST_TYPE)
			{
				fprintf(stderr, "Invalid type for one-less-car\nLine number: %d\n", line_number);
				exit(1);
			}
			return *(proftalk_expr_t *)pop(&list.expressions);
		}
		case COME_FROM_BEHIND:
		{
			proftalk_expr_t list = eval(*(proftalk_expr_t *)pop(args), env);
			if (list.type != LIST_TYPE)
			{
				fprintf(stderr, "Invalid type for one-less-car\nLine number: %d\n", line_number);
				exit(1);
			}
			pop(&list.expressions);
			return list;
		}
		case MAP:
		{
			proftalk_expr_t function = *(proftalk_expr_t *)pop(args);
			proftalk_expr_t list = eval(*(proftalk_expr_t *)pop(args), env);
			proftalk_expr_t retval;
			retval.type = LIST_TYPE;
			retval.expressions = makeList();
			while (list.expressions.head != NULL)
			{
				proftalk_expr_t ele = *(proftalk_expr_t *)pop(&list.expressions);
				proftalk_expr_t call;
				call.type = LIST_TYPE;
				call.expressions = makeList();
				pushBack(&call.expressions, &function);
				pushBack(&call.expressions, &ele);

				proftalk_expr_t *temp = malloc(sizeof(proftalk_expr_t));
				*temp = eval(call, env);
				pushBack(&retval.expressions, temp);
			}
			return retval;
		}
		case FILTER:
		{
			proftalk_expr_t function = *(proftalk_expr_t *)pop(args);
			proftalk_expr_t list = eval(*(proftalk_expr_t *)pop(args), env);
			proftalk_expr_t retval;
			retval.type = LIST_TYPE;
			retval.expressions = makeList();
			while (list.expressions.head != NULL)
			{
				proftalk_expr_t ele = *(proftalk_expr_t *)pop(&list.expressions);
				proftalk_expr_t call;
				call.type = LIST_TYPE;
				call.expressions = makeList();
				pushBack(&call.expressions, &function);
				pushBack(&call.expressions, &ele);

				proftalk_expr_t res = eval(call, env);
				if (res.type != LITERAL_TYPE)
				{
					fprintf(stderr, "Invalid type for the result of a filter expression\nLine number: %d\n", line_number);
					exit(1);
				}
				if (res.value != 0)
				{
					proftalk_expr_t *temp = malloc(sizeof(proftalk_expr_t));
					*temp = ele;
					pushBack(&retval.expressions, temp);
				}
			}
			return retval;
		}
		case CONS:
		{
			proftalk_expr_t retval;
			retval.type = LIST_TYPE;
			retval.expressions = makeList();
			int i;
			for (i=0;i<2;++i)
			{
				proftalk_expr_t *temp = malloc(sizeof(proftalk_expr_t));
				*temp = eval(*(proftalk_expr_t *)pop(args), env);
				pushBack(&retval.expressions, temp);
			}
			return retval;
		}
		case EMPTY:
		{
			proftalk_expr_t list = eval(*(proftalk_expr_t *)pop(args), env);
			if (list.type != LIST_TYPE)
			{
				fprintf(stderr, "Invalid argument to empty?\nLine number: %d\n", line_number);
				exit(1);
			}
			proftalk_expr_t retval;
			retval.type = LITERAL_TYPE;
			if (list.expressions.head == NULL)
				retval.value = 1;
			else
				retval.value = 0;
			return retval;
		}
		case PRINT:
			print_expr(eval(*(proftalk_expr_t *)pop(args), env));
			puts("");
			return;
				
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
			return handleBinary(function_id, args, env, line_number);
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
			proftalk_expr_t temp = *(proftalk_expr_t *)pop(&expr.expressions);
			proftalk_expr_t function = eval(temp, &env);
			switch(function.type)
			{
				case KEYWORD_TYPE:
					return handleBuiltIn(function.value, &expr.expressions, &env, temp.line_number, parent_env);
				case LAMBDA_TYPE:
					return evalLambda(function, &expr.expressions, &env);
			}
			printf("Failed to get function from type: %d\nAt line number: %d\n", function.type, temp.line_number);
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
