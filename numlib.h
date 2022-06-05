#include <stdio.h>

#define fuck {1,2,3}

#ifndef numlib_h
#define numlib_h

#define ERRNO   0
#define ERRARG  1
#define ERRFAIL 2

#define ABS(x) (x < 0 ? -x : x)

char* errStr(int flag)
{
	switch (flag) {
	case ERRNO:
		return "no error";
	case ERRARG:
		return "invalid argument";
	case ERRFAIL:
		return "algorithm failed to converge";
	default:
		return "unknown error";
	}
}

// bisection method solves for f(x)=0
// input: function, [a,b], tolerance, number of iterations, error flag
// output: approximate p s.t. f(p)~0
double bisectRoot(double (*f)(double x), double a, double b, double eps, unsigned int N, int *flag) // TODO: add option to auto-find bounds
{
	if ((f(a)*f(b) >= 0) || (a >= b)) {
		*flag = ERRARG;
		return 1;
	}
	
	int i = 0;
	double p = 0;
	while (++i <= N) {
		p = a + (b - a) / 2;
		if (ABS((b-a) / 2) < eps) // tolerance is based on the smallest addition we make, NOT how close the solution is to zero
			return p;
		else if (f(a)*f(p) > 0)
			a = p;
		else 
			b = p;
	}
	
	*flag = ERRFAIL;
	return p;
}

// fixed-point iteration solves for f(x)=x
// input: function, initial guess, tolerance, number of iterations, error flag
// output: approximate p s.t. f(p)~p
double fixedPoint(double (*f)(double x), double p0, double eps, unsigned int N, int *flag) // this algorithm sucks balls, it's assumed the user has a good starting point
{
	int i = 0;
	double p = 0;
	while (++i <= N) {
		p = f(p0);
		if (ABS(p - p0) < eps)
			return p;
		p0 = p;
	}
	
	*flag = ERRFAIL;
	return p;
}

// Newton-Raphson method solves for f(x)=0
// input: function, initial guesses, tolerance, number of iterations, error flag
// output: approximate p s.t. f(p)~0
double newtonRaphson(double (*f)(double x), double p0, double p1, double eps, unsigned int N, int *flag) // allow user to specify derivative?
{
	int i = 0;
	double p = 0;
	double q0 = f(p0);
	double q1 = f(p1);
	while (++i <= N) {
		p = p1 - q1*(p1 - p0) / (q1 - q0);
		if (ABS(p - p1) < eps)
			return p;
		p0 = p1;
		q0 = q1;
		p1 = p;
		q1 = f(p);	
	}
	
	*flag = ERRFAIL;
	return p;
}

#endif





