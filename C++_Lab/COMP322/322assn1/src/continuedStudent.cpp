#include "continued.h"

unsigned int gcd(unsigned int a, unsigned int b) {
	/* The Euclidean algorithm can be used compute the greatest common divisor of two integers a and b
	 * (assume 0 < a < b). It is based on a very simple rule: if q and r are the quotient and remainder
	 * of b divided by a (b = a * q + r and r < a), then gcd(a, b) = gcd(r, a). Write an algorithm to
	 * compute the GCD of two numbers based on this rule (the base case should be gcd(0, x) = x).
	 */
	// base case: gcd(0, x) = x
	if (a == 0) return b;
	else {
		int r = b % a;		// assert: 0 <= r < a
		return gcd(r, a);
	}
}

unsigned int gcdFaster(unsigned int a, unsigned int b) {
	/* A much quicker version is based on rules that do not depend on integer division:
	 * gcd(x, y) = gcd(y, x)
	 * gcd(2x, 2y) = 2 * gcd(x, y)
	 * gcd(2x, 2y + 1) = gcd(x, 2y + 1)
	 * if x > y, gcd(2x + 1, 2y + 1) = gcd(x - y, 2y + 1)
	 * Write an algorithm that uses only division by 2 and subtraction to compute the GCD of two numbers.
	 * For fun, try to avoid division altogether y using only bitwise operations (no division!)
	 * ^ This is more efficient anyway, no?
	 */
	// base case: gcd(0, x) = x
	if (a == 0) return b;
	int ra = a % 2;
	int rb = b % 2;
	if (ra == 0) {										// a is even
		if (rb == 0) return 2*gcdFaster(a>>2, b>>2);	// b is even
		else		 return gcdFaster(a>>2, b);			// b is odd
	}
	else {												// a is odd
		if (rb == 0) return gcdFaster(a, b>>2);			// b is even
		else {		 									// b is odd
			int x = (a-1)/2;
			int y = (b-1)/2;
			if (x > y)	return gcdFaster((x-y), b);
			else		return gcdFaster((y-x), a);
		}
	}
}

ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
  // compute continued fraction of b/a (NT a/b), assuming b > a
	ContinuedFraction fract = new ContinuedFraction;

	fract.head = b / a;
	int r = b % a;
	if (r == 0) {						// base case
		fract.tail = nullptr;
		return fract;
	}
	else {								// there is a remained, and we continue the continued fraction
		fract.tail = getCFlargerThanOne(a, r);
	}

	return &fract;
}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {
/* assume x > 1 and that continued fraction of x looks as
 * x = x0 + 1/x'    for x0 > 0 and x' > 1
 * Then:
 * 1/x = 0 + 1/x = 0 + 1/(x0 + 1/x')
 * if x > 1 and the continued fraction of x is [x0; x1, x2, ...],
 * what is the continued fraction of 1/x?
 * compute the continued fraction of any positive integer (using Q3)
 */
// what do a & b have to do with it?

}


ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
  // your code here

}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
  // your code here
}
