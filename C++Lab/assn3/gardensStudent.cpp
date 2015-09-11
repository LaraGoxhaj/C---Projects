#include "gardens.h"
#include <stack>
#include <iostream>
#include <math.h>





/* QUESTION 1 */
Fraction ContinuedFraction::getApproximation(unsigned int k) const {
    Fraction toRet;

    resetIterator();		// reset iterator before for safety

    // start with 1/0
    toRet.numerator = 1,
    toRet.denominator = 0;

    unsigned int z = 0;
    stack<cf_int> x;

    while (!hasNoMore() && z < k) {
    	x.push(next());
        z++;

    }

    resetIterator();

    if (!x.empty()) {
    	cf_int current = x.top();
    	x.pop();
    	toRet.numerator *= current;
    	toRet.denominator = 1;
    }

    while (!x.empty()) {
    	cf_int n = toRet.denominator;
    	cf_int d = toRet.numerator;
    	toRet.denominator = d;
    	toRet.numerator = d * x.top() + n;
    	x.pop();
    }

    return toRet;
}





/* QUESTION 2 */
// constructor computes the fixed part vector of integers for this cf
// we call the PeriodicCF constructor manually as there is none taking no parameters
RationalCF::RationalCF(Fraction frac) : PeriodicCF({}, {}) {
	// we note that every rational number can be represented as a finite continued fraction
	// we take that finite representation to be the "fixed part" of the continued fraction
	cf_int num = frac.numerator,
		   den = frac.denominator;

	// if denominator is 0, then we leave the vector empty
	if (den != 0) {
		cf_int rem;
		do {
			fixedPart.push_back(num/den);	// we have access to the base class's protected data
			rem = num % den,
			num = den,
			den = rem;
		} while (rem != 0);
	}
}


// destructor : make sure it deallocates all memory allocated using 'new'
RationalCF::~RationalCF() {
	// nothing of its own to deallocate
	// destructors are called automatically in the reverse order of construction (base classes last).
	// Do not call base class destructors.
}





/* QUESTION 3*/
// returns the next integer in the cf representation
cf_int PeriodicCF::next() const {
	cf_int toRet;

	if (hasNoMore()) {
		//resetIterator();
		toRet = -1;					// what should this return??
	}
	else {
		// for RationalCF, if !hasNoMore(), automatically fall into 1st case (if), so don't have to worry about
		// % periodicPart.size() -> % 0 (which would produce undefined behavior)
		if (*iteratorPosition < fixedPart.size()) {
			toRet = fixedPart[*iteratorPosition];
		}
		else {
			toRet = periodicPart[ (*iteratorPosition - fixedPart.size()) % periodicPart.size() ];
		}
		(*iteratorPosition)++;

	}
	return toRet;
}


// returns true iff the iterator reached the end
bool PeriodicCF::hasNoMore() const {
	if (periodicPart.size() == 0  &&  *iteratorPosition >= fixedPart.size())
			return true;
		else
			return false;
}


// resets the iterator over the cf to the beginning
void PeriodicCF::resetIterator() const {
    *iteratorPosition = 0;
}


PeriodicCF::~PeriodicCF() {
    delete iteratorPosition;	// deallocate iterator
}





/* QUESTION 4*/
MagicBoxCF::MagicBoxCF(const ContinuedFraction *f, cf_int a, cf_int b) : boxedFraction{f}, a{a}, b{b} {
	mbnums = new cf_int[4];		// must declare this on the heap as it may be called again
	resetIterator();
}


cf_int MagicBoxCF::next() const {

	// while the indices are not yet ready to spit q
	while( ((mbnums[2] == 0 || mbnums[3] == 0) && !(mbnums[2] == 0 && mbnums[3] == 0)) ||
            (mbnums[2] != 0 && mbnums[3] != 0 && mbnums[0] / mbnums[2] != mbnums[1] / mbnums[3]) ) {

		// no more integers to spit from cf
		if(boxedFraction->hasNoMore()) {
			boxedFraction->resetIterator();
			mbnums[0] = mbnums[1];
			mbnums[2] = mbnums[3];
            continue;
		}

		//change box accordingly
		int p = boxedFraction->next();
		int i = mbnums[1],
            j = mbnums[0] + mbnums[1] * p,
			k = mbnums[3],
			l = mbnums[2] + mbnums[3] * p;
		mbnums[0] = i;
		mbnums[1] = j;
		mbnums[2] = k;
		mbnums[3] = l;
    }
    // if we reached the end of the cf - return -1
	if (hasNoMore()) {
		//resetIterator();
		return -1;
	}

    // return q and change box accordingly
	int q = mbnums[0] / mbnums[2];
	int i = mbnums[2],
        j = mbnums[3],
		k = mbnums[0] - mbnums[2] * q,
		l = mbnums[1] - mbnums[3] * q;
	mbnums[0] = i;
	mbnums[1] = j;
	mbnums[2] = k;
	mbnums[3] = l;
	return q;
}


bool MagicBoxCF::hasNoMore() const {
	if (mbnums[2] == 0 && mbnums[3] == 0)
		return true;
	else
		return false;
}


void MagicBoxCF::resetIterator() const {
	boxedFraction->resetIterator();
	mbnums[0] = a;
	mbnums[1] = b;
	mbnums[2] = 1;
	mbnums[3] = 0;
}


MagicBoxCF::~MagicBoxCF() {
	// needn't delete boxedFraction, as CF is a base class of this one,
	// thus its destructor will automatically be called (?)
    delete mbnums;
}





/* QUESTION 5*/
ostream &operator<<(ostream& outs, const ContinuedFraction &cf) {
	int max = 10;	// max number of ints to print
	cf.resetIterator();

	outs << "[";
	if (!cf.hasNoMore()) {
		outs << cf.next();				// always print the integer part, if available
		max--;
	}
	if (!cf.hasNoMore()) {
		outs << "; " << cf.next();		// print out second
		max--;
	}
	if (!cf.hasNoMore()) {				// print out rest separated by comma
		do {
			outs << ", " << cf.next();
			max--;
		} while (!cf.hasNoMore() && max > 0);
	}
	if (max == 0 && !cf.hasNoMore())	// check to see if anything left out
		outs << ",...";
	outs << "]";
	return outs;
}





/* QUESTION 6 */
Flower::Flower(const ContinuedFraction *f, unsigned int apxLengthParam) : theta(f), apx_length(apxLengthParam) {}


float Flower::getAngle(unsigned int k) const {
	Fraction fr = theta->getApproximation(apx_length);
	fr.numerator = fr.numerator % fr.denominator;		// keep only fractional part

	// compute fractional part of the rotations
	float fractpart = ( (k * fr.numerator) % fr.denominator / (float)fr.denominator );
	return (2 * pie * fractpart);
}


Seed Flower::getSeed(unsigned int k) const {
	Seed s;

	// we follow the formulas in the assignment's document
	float angle = getAngle(k);
	s.x = sqrt(k/pie) * cos(angle);
	s.y = sqrt(k/pie) * sin(angle);
	return s;
}


vector<Seed> Flower::getSeeds(unsigned int k) const {
	vector<Seed> flower;
	for (unsigned int i = 0; i < k; i++)
		flower.push_back(getSeed(i));
	return flower;
}


Flower::~Flower() {
   // delete theta;
}





/* QUESTION 7*/
void Flower::writeMVGPicture(ostream &out, unsigned int k, unsigned int scale_x, unsigned int scale_y) const {
	// k = N = total number seeds to be drawn on canvas
	// scale_x = H
	// scale_y = W

	if ((scale_x - 200)/2 < 1)
		scale_x = 202;
	if ((scale_y - 200)/2 < 1)
		scale_y = 202;

	vector<Seed> flower = getSeeds(k);

	for (unsigned int i = 0; i < k; i++) {
		int C_x = (scale_x/2) + flower[i].x * (scale_x-200)/2 * sqrt(pie/k);
		int C_y = (scale_y/2) + flower[i].y * (scale_y-200)/2 * sqrt(pie/k);

		unsigned int min = (scale_x > scale_y) ? scale_y : scale_x;

		int B_x = C_x + sqrt((float)i/k) * min/100.0;
		int B_y = C_y;

		out << "fill blue circle " << C_x << "," << C_y << " " << B_x << "," << B_y << endl;
	}




}
