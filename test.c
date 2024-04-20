#include <stdio.h>

#include "malib.h"

static int TEST_RET = 0;

static char *TEST_STR01 = "Hello, malib!";


int test_str_len() {

	int ret = 0;

	int sl = str_len(TEST_STR01);
	if (sl != 13)
		ret = -1;

	return ret;
}


int main(int argc, char **argv) 
{
	(void) argc;
	(void) argv;

	if (test_str_len() < 0) 
		TEST_RET = -1;

	if (TEST_RET < 0)
		fprintf(stderr, "FAILED\n");
	else
		fprintf(stderr, "OK\n");
		
	return TEST_RET;
}
