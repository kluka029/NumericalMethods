#include <stdio.h>

#ifndef testFramework_h
#define testFramework_h

static int numTests = 0;
static void (*testList [1024])(void); // TODO: figure out how to dynamically allocate?
						 
#define TEST(name, body) \
	void name() \
	{ \
		int result = 1; \
		printf("%s:\n", __func__); \
		body \
	}
	
// TODO: how to make it so name does not have to be passed as string?
#define SUB_TEST(name, body) \
	printf("Start subtest, %s.%s\n", __func__, name); \
	body \
	printf("End subtest, %s.%s, Result = %s\n", __func__, name, (result ? "PASSED" : "FAILED")); \
	result = 1;
	
#define ASSERT_TRUE(x) result = result && x;

// TODO: there has to be a way to do this using precompiler/compiler
#define RUN_TESTS \
	int main() \
	{ \
		for (int i = 0; i < numTests; i++) { \
			testList[i](); \
		} \
	}

#endif