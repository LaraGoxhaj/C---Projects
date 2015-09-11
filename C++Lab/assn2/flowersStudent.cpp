#include "flowers.h"
#include <cmath>
#define M_PI 3.14159265358979323846264338327


ContinuedFraction fractionalPart(ContinuedFraction &f) {
	ContinuedFraction* x = new ContinuedFraction(f);
	if (!x->fixedPart.empty())
		x->fixedPart[0] = 0;
	else if (!x->periodicPart.empty())
		x->fixedPart.insert(x->fixedPart.begin(), 0);
	else {
		x->fixedPart.insert(x->fixedPart.begin(), 0);
		x->periodicPart.insert(x->periodicPart.begin(), 0);
	}
	return *x;
}


unsigned int spitSqrt8(unsigned int index) {
	// sqrt 8 is [2; 1, 4, ...]
	if (index == 0) return 2;
	if (index % 2 != 0) return 1;
	return 4;
}


unsigned int spitEulerSquare(unsigned int index) {
	// [7; 2, 1, 1, 3, 18, 5, 1, 1, 6, 30, 8, 1, 1, 9, 42, 11, 1, 1, 12, 54, 14, 1, 1, 15, ...]
	int x = 0;
	if (index == 0)
		x = 7;
	else switch (index % 5) {
		case 0:
			x = 6 + (index/5)*12;
			break;
		case 1:
			x = 2 + (index/5)*3;
			break;
		case 2:
		case 3:
			x = 1;
			break;
		case 4:
			x = 3 + (index/5)*3;
			break;
	}
	return x;
}


Fraction getApproximation(ContinuedFraction &fr, unsigned int n) {
	Fraction* result = new Fraction;
	unsigned int ffrsize = fr.fixedPart.size();
	unsigned int pfrsize = fr.periodicPart.size();

	// 0 integer approximation, or entirely empty fraction
	if (n == 0 || ffrsize + pfrsize == 0) {
		result->numerator = 0;
		result->denominator = 0;
	}

	// 1 integer approximation
	else if (n == 1) {
		if (n <= ffrsize)
			result->numerator = fr.fixedPart[0];
		else
			result->numerator = fr.periodicPart[0];
		result->denominator = 1;
	}

	// 2+ integer approximation
	else {
		Fraction f;
		if (ffrsize > 0) {
			int x = fr.fixedPart[0];
			fr.fixedPart.erase(fr.fixedPart.begin());
			f = getApproximation(fr, --n);
			result->numerator = x * f.numerator + f.denominator;
		}
		else {		// psize > 0 but fsize = 0
			int x = fr.periodicPart[0];
			fr.periodicPart.push_back(x);
			fr.periodicPart.erase(fr.periodicPart.begin());
			f = getApproximation(fr, --n);
			result->numerator = x * f.numerator + f.denominator;
		}
		result->denominator = f.numerator;
	}

	return *result;
}


double getAngle(ContinuedFraction &theta, int k) {
    ContinuedFraction fractTheta = fractionalPart(theta);
    Fraction fTheta = getApproximation(fractTheta, 7);
    fTheta.numerator *= k;
    fTheta.numerator = fTheta.numerator % fTheta.denominator;
    double x = 2.0 * M_PI * double(fTheta.numerator) / double(fTheta.denominator);
    double y = 2.0 * M_PI;
    return fmod(x,y);
}


Seed getSeed(ContinuedFraction &theta, int k) {
	Seed* s = new Seed;
	s->x = sqrt(k/M_PI) * cos(getAngle(theta, k));
	s->y = sqrt(k/M_PI) * sin(getAngle(theta, k));
	return *s;
}


void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
	int num = flower.size();
	Seed s = getSeed(theta, num);
	flower.push_back(s);
}


int spitNextMagicBox(MagicBox &box) {
	// reached end of a+bx
	if (box.k == 0 && box.l == 0)
		return 0;

	// did not reach end of a+bx
	else {
		int q0 = (box.i / box.k);
		int i = box.i;
		int j = box.j;

		// same integer part, q0 = q1
		if (q0 == (box.j / box.l)) {
			// change magic numbers
			box.i = box.k;
			box.j = box.l;
			box.k = i - q0*box.k;
			box.l = j - q0*box.l;
			// return integer part
			return q0;
		}

		// different integer part, q0 != q1
		else {
			int p;
			int fsize = box.boxedFraction.fixedPart.size();
			int psize = box.boxedFraction.periodicPart.size();
			int index = box.indexInBoxedFraction;
			if (index < psize) {
				if (index < fsize)
					p = box.boxedFraction.fixedPart[index];
				else
					p = box.boxedFraction.periodicPart[index-fsize];
				int k = box.k;
				int l = box.l;
				box.i = j;
				box.j = i + j*p;
				box.k = l;
				box.l = k + l*p;
				box.indexInBoxedFraction++;
			}
			else {		// reached end of the continuedFraction
				box.i = j;
				box.k = box.l;
				box.indexInBoxedFraction = 0;
			}
			return spitNextMagicBox(box);
		}
	}
}


ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
    MagicBox* box = new MagicBox;
    box->boxedFraction = f;
    box->i = a;
    box->j = b;
    box->k = 1;
    box->l = 0;
    ContinuedFraction* fr = new ContinuedFraction;
    int y, i = 0;
    while (i < length) {
    	y = spitNextMagicBox(*box);
    	if (y == 0)
    		break;
    	else {
    		fr->fixedPart[i] = y;
    		i++;
    	}
    }

    // no periodic part
	return *fr;
}
