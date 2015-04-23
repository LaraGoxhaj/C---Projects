#include "eden.h"

#include <stack>


/* Question 2 : 0-credit */

/*  getting an approximation using the new Fraction class */
Fraction<cf_int> ContinuedFraction::getApproximation(unsigned int k) const {
	if (k == 0)
		throw 0;

	// start with 1/0
	Fraction<cf_int> toRet;
	toRet.getNumerator() = 1;
	toRet.getDenominator() = 0;

	// we go backwards from the end to the beginning to compute the approximation
	// to do this, we need to collect on a stack all the numbers we'll use for the apx
	stack<cf_int> ints;
	// construct a new iterator
	Iterator it;
	while (!it.isDone() && k-- > 0) {
		ints.push(getIterator()->next());
	}

	Fraction<cf_int> temp;
	// do the math for adding an integer to a partial solution:
	// x + 1 / (n / d) = x + d / n = (x*n + d) / n
	while (!ints.empty()) {
		cf_int x = ints.top();
		cf_int n = toRet.getNumerator();
		cf_int d = toRet.getDenominator();
		toRet(n, d);
		toRet.invert();
		temp(x, 1);
		toRet = toRet * temp;
		ints.pop();
	}
	return toRet;
}

/* Building a rational cf using the new Fraction class*/
RationalCF::RationalCF(Fraction<cf_int> frac) {
	frac.check();
	PeriodicCF();

	if (frac.getNumerator() == 0) { // if the fraction is 0
		fixedPart.push_back(0);
		return;
	}

	// same as getCFlargerThanOne from hw1
	while (frac.getDenominator() != 0) {
		if (frac.getNumerator() != 0) {
			fixedPart.push_back(frac.getNumerator() / frac.getDenominator());
		}
		auto tmp = frac.getNumerator() % frac.getDenominator();
		int num = frac.getDenominator();
		int den = tmp;
		frac(num, den);
	}
}

/* Question 3 : Euler squared */

Iterator *EulerSquared::getIterator() const {
	EulerSquaredIterator* e2It = new EulerSquaredIterator();
	return e2It;
}


cf_int EulerSquaredIterator::next() {
    // [7 ; 2, 1, 1, 3, 18, 5, 1, 1, 6, 30, 8, 1, 1, 9, 42, 11, 1, 1 ...];
	cf_int toRet;
	if(index == 0) toRet = 7; // first item
	if(index == 1) toRet = 2; // second item
	if(index % 5 == 2 || index%5 == 3) toRet = 1; // all the 1s
	if(index % 5 == 4) toRet = index/5 * 3 + 3; //3,6,9,12...etc
	if(index % 5 == 0) toRet = index/5 * 12 + 6; // 18, 30, 42, etc...
	toRet = index/5 * 3 + 2; // 5,8,11,14 etc....

	index++;
	return toRet;
}

bool EulerSquaredIterator::isDone() const {
    return false;
}


/* Question 4 : PeriodicCF iterator*/

Iterator *PeriodicCF::getIterator() const {
	PeriodicCFIterator* pCFIt = new PeriodicCFIterator();
	return pCFIt;
}

cf_int PeriodicCFIterator::next() {
	if (isDone())	throw -1.0;

	it++;
	if (it < cf.fixedPart.size())
		return cf.fixedPart[it];
	else {	// is in periodic part
		unsigned int positionInPeriodic = (it - cf.fixedPart.size()) % cf.periodicPart.size();
		return cf.periodicPart[positionInPeriodic];
	}
}

bool PeriodicCFIterator::isDone() const {
	return cf.periodicPart.empty() // if not periodic
	    	            && it >= cf.fixedPart.size(); // and done with the fixed part

}


/* Question 5 : MagicBoxCF iterator */

Iterator *MagicBoxCF::getIterator() const {
	Iterator* cf = boxedFraction.getIterator();
    MagicBoxCFIterator* mbCFIt = new MagicBoxCFIterator(cf, a, b);
    return mbCFIt;
}

cf_int MagicBoxCFIterator::next() {
	if (isDone())	return 0;

	cf_int q = i / k;
	cf_int ii = k,
		   jj = l,
		   kk = i - k * q,
		   ll = j - l * q;
	i = ii;
	j = jj;
	k = kk;
	l = ll;

	return q;
}

bool MagicBoxCFIterator::isDone() const {
    // updateIndeces();	????
	return (k == 0 && l == 0);
}



