#include <stdio.h>

#include "malib.h"

static int TEST_RET = 0;

static char *TEST_STR01 = "Hello, malib!";
static char *TEST_STR02 = "Huqmkvello, maioal";

int test_str_len() {

	int ret = 0;

	if (ma_strlen(TEST_STR01) != 13)
		ret = -1;

	if (ma_strlen(TEST_STR02) != 18)
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
