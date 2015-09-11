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
	// a is even
	if (ra == 0) {
		if (rb == 0) return 2*gcdFaster(a>>2, b>>2);	// b is even
		else		 return gcdFaster(a>>2, b);	// b is odd
	}
	// a is odd
	else {
		if (rb == 0) return gcdFaster(a, b>>2);		// b is even
		else {		 				// b is odd
			int x = (a-1)/2;
			int y = (b-1)/2;
			if (x > y)	return gcdFaster((x-y), b);
			else		return gcdFaster((y-x), a);
		}
	}
}

ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
  // compute continued fraction of b/a (NT a/b), assuming b > a
	ContinuedFraction* result = new ContinuedFraction;
	result->head = b / a; // the quotient - integer part
	result->tail = (b % a == 0) ?
			nullptr : //base case
			getCFlargerThanOne(a, b % a); // recursive call
	return result;
}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {
	// if b < a,b / a = 0  and b % a = b
	return getCFlargerThanOne(b, a);
}


ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
	ContinuedFraction *toRet = new ContinuedFraction; //will be returned
	toRet->head = head;

	//we will have two iterators, one over the parameter, one over a copy of the parameter
	ContinuedFraction *iterateFixed = fixed;
	ContinuedFraction *iteratetoRet = toRet;
	while(iterateFixed != nullptr) {
		iteratetoRet->tail = new ContinuedFraction; //create a new struct to store the saved data
		iteratetoRet = iteratetoRet->tail;
		iteratetoRet->head = iterateFixed->head;
		// continue over the parameter cf
		iterateFixed = iterateFixed->tail;
	}

	// we do the same for the period
	ContinuedFraction *iterateperiod = period;
	ContinuedFraction *periodTmp = period;
	bool first = true; // we will connect the end of the fixed copy to the first el. of the period
	while(iterateperiod != nullptr) {
		iteratetoRet->tail = new ContinuedFraction; //create a new struct to store the saved data
		if(first) { // connect fixed to period
			periodTmp = iteratetoRet->tail;
			first = false;
		}
		iteratetoRet = iteratetoRet->tail;
		iteratetoRet->head = iterateperiod->head;
		// continue over the parameter cf
		iterateperiod = iterateperiod->tail;
	}

	// connect the end of the fixed copy to the start of the fixed period
	iteratetoRet->tail = periodTmp;
	return toRet;
}
}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
	Fraction toRet; // will be returned
	if (fr == nullptr) return toRet; //return shit if fr is nullptr
	if(n <= 1 || fr->tail == nullptr) { //base case
		//either we reached the end of the cf, or we want to print one int only
		toRet.numerator = fr->head;
		toRet.denominator = 1;
	} else {
		// make a recursive call
		Fraction f = getApproximation(fr->tail, n-1);
		// we need (head + 1/f) = head + f.den / f.num = (head * f.num + f.den) / f.num
		toRet.numerator = fr->head * f.numerator + f.denominator;
		toRet.denominator = f.numerator;
	}
	return toRet;
}
