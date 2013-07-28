#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "lexer.h"
#include "env.h"

proftalk_expr_t eval(proftalk_expr_t expr, env_t *parent_env);

#endif
