#include <string.h>
#include "env.h"

int env_find(env_t *env, char *name, proftalk_expr_t *result)
{
	if (env == NULL)
		return 0;
	node_t *var = env->vars.head;
	while (var != NULL)
	{
		pair_t realvar = *(pair_t *)var->data;
		if (!strcmp(realvar.key, name))
		{
			*result = realvar.val;
			return 1;
		}
		var = var->next;
	}
	return env_find(env->parent, name, result);
}

void env_insert(env_t *env, char *name, proftalk_expr_t val)
{
	pair_t *newVar = malloc(sizeof(pair_t));
	newVar->key = name;
	newVar->val = val;
	pushBack(&env->vars, newVar);
}
