//
//  baf.h
//  baf
//
//  Created by Gheorghe Comanici on 2015-02-26.
//  Copyright (c) 2015 Comanici Gheorghe. All rights reserved.
//



#include <iostream>

#ifndef baf_baf_h
#define baf_baf_h



class complex {
private:
    double real;
    double imaginary;
public:
    // class-name(c.s.-param-list) c.s.-data-init {more-code}
    complex(double r, double i) : real{r}, imaginary{i} {std::cout << "...buiding a complex number, using complex(double,double)..." << std::endl;}
        complex(double r) : real{r}, imaginary{0.0} {std::cout << "...buiding a complex number, using complex(double)..." << std::endl;}
    complex(); // I don't have it's implementation
    // copy constructor
        complex(complex &other) : real{other.real}, imaginary{other.imaginary} {std::cout << "...buiding a complex number, using the copy constructor complex(&double)..." << std::endl;}

    //destructor
    ~complex() {
        std::cout << "...destroying a complex number..." << std::endl;
    }


    double getReal() const {return real;}
    double getImaginary() const; // I don't have it's implementation

    void setReal(double r); // I don't have it's implementation
    void setImaginary(double i) {imaginary = i;}

    //OPERATOR OVERLOADING

    complex &operator+=(complex other);
    complex &operator-=(complex other);
    complex &operator*=(complex other);
    complex &operator/=(complex other);

    complex operator*(const complex &second) const;
    complex operator+(const complex &second) const;


    // FRIEND METHODS - NOT MEMBER

    friend std::ostream &operator<<(const std::ostream&, const complex&);
};



#endif
