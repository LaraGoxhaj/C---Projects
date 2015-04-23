
/* QUESTION 1 */

/* We will build a general fraction class using templates provide code for all methods listed as TODO*/ 

#ifndef hw4_fraction_h
#define hw4_fraction_h

#include <iostream>

template<typename T>
class Fraction {
private:
    T numerator;
    T denominator;
public:
    void check() {
    	// should I simplify?
    	if (denominator == (T)0 && numerator == (T)0)
    	    throw 0;
    	else if (denominator == (T)0)
    	 	numerator = (T)1;
    	else if (numerator == (T)0)
    	    denominator = (T)1;
    }

    Fraction(T num, T den): numerator{num}, denominator{den} {
        //TODO
    	check();
    }
    Fraction(T num) : numerator{num}, denominator{1} {}
    Fraction(const Fraction &f) : numerator{f.numerator}, denominator{f.denominator} { }
    
    //-- returns the numerator
    T getNumerator() const{
        return numerator;
    }

    //-- returns the denominator
    T getDenominator() const{
        return denominator;
    }
    
    //-- inverts the fraction: swaps denominator and numerator
    Fraction &invert() {
    	//TODO
    	T temp = numerator;
    	numerator = denominator;
    	denominator = temp;
    	check();
    	simplify();		// should I?
    	return this;
    }
    
    //-- adds the fraction f to the current fraction a/b + c/d = (a*d + b*c) / (b*d) (don't simplify!)
    Fraction &operator+=(const Fraction &f) {
        //TODO
    	int nTemp = (numerator * f.denominator) + (denominator * f.numerator);
    	int dTemp = denominator * f.denominator;
    	if (nTemp == 0 && dTemp == 0)
    		throw 0;
    	else {
    		numerator = nTemp;
    		denominator = dTemp;
    		check();
    		simplify();		// should I?
    		return this;
    	}
    }
    
    //-- adds the fraction f to the current fraction a/b + c/d = (a*d + b*c) / (b*d) (don't simplify!)
    Fraction operator+(const Fraction &f) const {
        //TODO
    	Fraction toRet;
    	toRet.numerator = (numerator * f.denominator) + (denominator * f.numerator);
    	toRet.denominator = denominator * f.denominator;
    	toRet.check();
    	toRet.simplify();	// should I?
    	return toRet;
    }
    
    //-- subtracts the fraction f from the current fraction a/b - c/d = (a*d - b*c) / (b*d) (don't simplify!)
    Fraction &operator-=(const Fraction &f) {
        //TODO
    	int nTemp = (numerator * f.denominator) - (denominator * f.numerator);
    	int dTemp = denominator * f.denominator;
    	if (nTemp == 0 && dTemp == 0)
    		throw 0;
    	else {
    		numerator = nTemp;
    		denominator = dTemp;
    		check();
    		simplify();	// should I?
    		return this;
    	}
    }
    
    //-- subtracts the fraction f from the current fraction a/b - c/d = (a*d + b*c) / (b*d) (don't simplify!)
    Fraction operator-(const Fraction &f) const {
        //TODO
    	Fraction toRet;
    	toRet.numerator = (numerator * f.denominator) - (denominator * f.numerator);
    	toRet.denominator = denominator * f.denominator;
    	toRet.check();
    	toRet.simplify();	// should I?
    	return toRet;
    }
    
    //-- multiplies the fraction f to the current fraction a/b * c/d = (a*c) / (b*d) (don't simplify!)
    Fraction operator*(const Fraction &f) const {
        //TODO
    	Fraction toRet;
    	toRet.numerator = numerator * f.numerator;
    	toRet.denominator = denominator * f.denominator;
    	toRet.check();
    	toRet.simplify();	// should I?
    	return toRet;
    }

    //-- divides the current fraction by f: (a/b) / (c/d) = (a*d) / (b*c) (don't simplify!)
    Fraction operator/(const Fraction &f) const {
        //TODO
    	Fraction toRet;
    	toRet.numerator = numerator * f.denominator;
    	toRet.denominator = denominator * f.numerator;
    	toRet.check();
    	toRet.simplify();	// should I?
    	return toRet;
    }
    
    //-- compares the current fraction to f.
    // * If both denominators are 0, return true (they are both infinity)
    bool operator==(const Fraction &f) const {
        //TODO
    	if (denominator == 0 && f.denominator == 0)
    		return true;
    	else
    		return ((double)numerator/denominator == (double)f.numerator/f.denominator);
    }
    
    //-- compares the current fraction to f for inequality.  use == above!!
    bool operator!=(const Fraction &f) const {
        //TODO
    	if (this == f)
    		return false;
    	else
    		true;
    }
    
    T quotient() const {
        if (denominator == 0 ) throw 1;
        return numerator / denominator;
    }
    
    void simplify() {
        if( numerator == denominator) {
            numerator = denominator = 1;
            return;
        }
        
        T &smaller = ( numerator < denominator ) ? numerator : denominator;
        // try all possible factors and simplify as long as possible
        for(T factor = 2; factor <= smaller; (factor == 2) ? factor++ : factor += 2) {
            while(numerator % factor == 0 && denominator % factor == 0) {
                numerator /= factor;
                denominator /= factor;
            }
        }
    }
    
    friend std::ostream& operator<<( std::ostream& os, const Fraction& f ) {
        os << "(" << f.numerator << "/" << f.denominator << ")";
        return os;
    }
};


#endif
