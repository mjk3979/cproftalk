#ifndef ENV_H
#define ENV_H
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"

typedef struct env_t env_t;

typedef struct
{
	char *key;
	proftalk_expr_t val;
} pair_t;

struct env_t
{
	ll_t vars;
	env_t *parent;
};

int env_find(env_t *env, char *name, proftalk_expr_t *result);

void env_insert(env_t *env, char *name, proftalk_expr_t val);

#endif
