#include <stdio.h>
#include <string.h>

#include "malib.h"

static int TEST_RT = 0;

#define TEST_FAIL(...)                                                         \
	{                                                                      \
		TEST_RT = -1;                                                  \
		fprintf(stderr, "FAILED %s:%d \"", __FILE__, __LINE__);        \
		fprintf(stderr, __VA_ARGS__);                                  \
		fprintf(stderr, "\"\n");                                       \
	}

static char *TEST_STR00 = "";
static char *TEST_STR01 = "Hello, malib!";
static char *TEST_STR02 = "huqmkvello, maioal";

void test_strlen()
{
	if (ma_strlen(TEST_STR00) != 0)
		TEST_FAIL("empty string should have length 0")

	if (ma_strlen(TEST_STR01) != 13)
		TEST_FAIL("wrong value returned")

	if (ma_strlen(TEST_STR02) != 18)
		TEST_FAIL("wrong value returned")
}

void test_toa()
{
	char	 buf[16];
	uint64_t n	  = 0x123cba9;
	char	*expected = "123cba9";
	size_t	 len	  = 7;

	if (ma_toa(buf, n, len) != len)
		TEST_FAIL("wrong value returned")

	if (memcmp(buf, expected, len) != 0)
		TEST_FAIL("conversion failed")
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	test_strlen();
	test_toa();

	return TEST_RT;
}
