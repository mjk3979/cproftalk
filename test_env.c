#include <assert.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "env.h"

int main(int argc, char **argv)
{
	env_t test = makeEnv(NULL);

	proftalk_expr_t test1;
	test1.type = 1;
	test1.value = 689;
	env_insert(&test, "testVar", test1);
	proftalk_expr_t test2;
	assert(env_find(&test, "testVar", &test2));
	assert(test2.type == 1);
	assert(test2.value == 689);

	assert(!env_find(&test, "gfnjkwenf", &test2));

	env_t super_test = makeEnv(&test);
	proftalk_expr_t test3;
	test3.type = 3;
	test3.value = 900011;
	env_insert(&super_test, "meh", test3);
	assert(env_find(&super_test, "meh", &test2));
	assert(test2.type == 3);
	assert(test2.value == 900011);

	assert(!env_find(&test, "meh", &test2));
	
	assert(env_find(&super_test, "testVar", &test2));
	assert(test2.type == 1);
	assert(test2.value == 689);

	assert(env_find(&test, "testVar", &test2));
	assert(test2.type == 1);
	assert(test2.value == 689);

	puts("All tests passed");

	return 0;
}
