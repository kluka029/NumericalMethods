#include "testFramework.h"
#include "../numlib.h"

double testFunc(double x)
{
	return x + 3.14159;
}

double testFunc2(double x)
{
	return x*x;
}

TEST(BisectRootTests,
	double eps = 0.001;
	int N = 100;
	int flag = ERRNO;
	double p = 0;
	
	SUB_TEST("FlagSetToERRARGWhenBoundsDontCaptureZero", 
		p = bisectRoot(testFunc, 0.0, 1.0, eps, N, &flag);
		ASSERT_TRUE(flag == ERRARG);
	)
	
	SUB_TEST("FlagSetToERRARGWhenAIsGreaterThanB",
		flag = ERRNO;
		p = bisectRoot(testFunc, 1.0, 1.0, eps, N, &flag);
		ASSERT_TRUE(flag == ERRARG);
	)
	
	SUB_TEST("RootFoundWhenBoundsAreEqualMagnitudeAndOppositeSign",
		flag = ERRNO;
		p = bisectRoot(testFunc, -4.0, 4.0, eps, N, &flag);
		ASSERT_TRUE((ABS(testFunc(p)) < eps));
		ASSERT_TRUE(flag == ERRNO);
	)
	
	SUB_TEST("RootFoundForBoundsOfDifferentMagnitudes",
		flag = ERRNO;
		p = bisectRoot(testFunc, -7.1542, 2.4539, eps, N, &flag);
		ASSERT_TRUE((ABS(testFunc(p)) < eps));
		ASSERT_TRUE(flag == ERRNO);
	)
	
	SUB_TEST("FlagSetToERRFAILWhenAlgorithmDoesNotConverge",
		flag = ERRNO;
		p = bisectRoot(testFunc, -7.1542, 2.4539, eps, 1, &flag);
		ASSERT_TRUE(flag == ERRFAIL);
	)
)

TEST(FixedPointTests,
	double eps = 0.001;
	int N = 100;
	int flag = ERRNO;
	double p = 0;

	SUB_TEST("FlagSetToERRFAILWhenAlgorithmDoesNotConverge",
		p = fixedPoint(testFunc, 0, eps, 1, &flag);
		ASSERT_TRUE(flag == ERRFAIL);
	)

	SUB_TEST("FixedPointFound",
		flag = ERRNO;
		p = fixedPoint(testFunc2, -0.5, eps, N, &flag);
		ASSERT_TRUE(flag == ERRNO); // TODO: need better requirements for these	
	)
)

TEST(NewtonRaphsonTests,
	double eps = 0.001;
	int N = 100;
	int flag = ERRNO;
	double p = 0;

	SUB_TEST("FixedPointFound",
		p = newtonRaphson(testFunc, -10, 10, eps, N, &flag);
		ASSERT_TRUE(flag == ERRNO);
	)
)

int main()
{
	void (*testList [1024])(void) = {BisectRootTests};
	testList[0]();
	//BisectRootTests();
	//FixedPointTests();
	//NewtonRaphsonTests();
}