#include <stdint.h>
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

#define XORSHIFT_SEED (1111)
#define XORSHIFT_SIZE (64)
const uint64_t XORSHIFT_EXPECT[XORSHIFT_SIZE] = { 0x117e3b5f19f,
	0x711586e1a4451dbc, 0x82518af724f37887, 0x5302425d26185fb6,
	0xf1d9563994a74289, 0x6a60147b3a978e4c, 0x33a19c5efc68b250,
	0x2e828cb9a39ef734, 0x589c40bee63687da, 0xc7ab06007e0a5c55,
	0x1980b0054cb1fdad, 0x3cdfb264ffce5516, 0xdc8a15ca977e4c3c,
	0xdc5909236b0c3fa4, 0xc1934cc8f4974edb, 0x24a71413c47ab686,
	0x8b22715bef59226b, 0xf9d04bad7f5c6aef, 0xae5850456c1189fa,
	0x1d61fb15fb469469, 0xa7ace5c5959a2301, 0xc4d2076bd257f707,
	0x8281de079cbc7929, 0xe7a5c8b7e4886b9b, 0xfa931a1f5f30fd8c,
	0x38d6341a4cee7f77, 0x5150cf71b0949e49, 0x410c4ea7ef710535,
	0xcd17babf48b60a7f, 0x9c2966dae9bc19ab, 0xea6bf2266ec6b58,
	0x34c05eb8df4c658e, 0xe8de896f4cd05ec5, 0x35e9dd3973f6ef38,
	0xd3102c3ab881cce6, 0x7c83fde2b9e136ff, 0xa82f918a74a4ab52,
	0x9feb5aba31057684, 0x3c12317710385d69, 0x2f655d9254845793,
	0xf7870eb96c32dbfc, 0x108e113ecbb5c14b, 0xe4bd5d2fd3699809,
	0x639e5d5cb75a6979, 0xe9248b23d257a3eb, 0x99a79846d8be966c,
	0x51d54d1848e7f040, 0xa89fd788e0c22fa0, 0x7ec51eff038243ff,
	0x4a4461a6e41a58b8, 0x7f4394f960414209, 0xec654a06f0a62cd,
	0x3e3dbfd96b856548, 0xb7cc36c8efa63d82, 0x33a3a1e6f2b45179,
	0xc58e719b975c479b, 0xf94786560c3879d4, 0xb3231f57594afc27,
	0x1e459211fafd801f, 0xe9760ec3efd59cdf, 0x77417232eebae026,
	0x1ac1d20cc1175c66, 0xb5b5a7272072ab5e, 0xc20dae4994e35988 };

void test_xorshift64()
{
	uint64_t state = XORSHIFT_SEED;
	uint64_t sampl[XORSHIFT_SIZE];

	for (size_t i = 0; i < XORSHIFT_SIZE; i++) {
		sampl[i] = ma_xorshift64(&state);
		// printf("0x%lx, ", sampl[i]);
	}
	for (size_t i = 0; i < XORSHIFT_SIZE; i++) {
		if (sampl[i] != XORSHIFT_EXPECT[i]) {
			TEST_FAIL("wrong value[%zu]=0x%lx (expected: 0x%lx)", i,
				sampl[i], XORSHIFT_EXPECT[i])
			break;
		}
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	test_strlen();
	test_toa();
	test_xorshift64();

	return TEST_RT;
}
