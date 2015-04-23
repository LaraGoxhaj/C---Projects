#include "baf.h"

using namespace std;


// class-name::class-name(c.s.-params) ...rest...
complex::complex() : real{0.0}, imaginary{0.0} {std::cout << "...buiding a complex number, using default constructor complex()..." << std::endl;}

//return-type class-name::method-name(c.s.-params) { code }
double complex::getImaginary() const { return imaginary;}

void complex::setReal(double r) { real = r; }

complex& complex::operator+=(complex other) {
    (*this).real += other.real;
    this->imaginary += other.imaginary;
    return *this;
}

complex& complex::operator*=(complex other) {
    real = real * other.real - imaginary * other.imaginary;
    imaginary = real * other.imaginary
    + other.real * imaginary;
    return *this;
}


complex complex::operator+(const complex &second) const {
    complex c(real + second.real, imaginary + second.imaginary);
    return c;
}


ostream& operator<<(ostream& outs, const complex& num) {
    return outs << num.getReal() << " + " << num.getImaginary() << "i";
}


int main(int argc, const char * argv[]) {

    complex ada(1.0, 3.0); // ada is 1+3i
    complex bee(2.0, 1.0); // bee is 2+1i
    complex com(3.0); // com is 3
    complex doors; // doors is 0

    ada += bee;
    cout << ada.getReal() << " + " << ada.getImaginary() << "i" << endl;
    // prints 3.0 + 4.0i

    // The following does not compile!
    //cout << ada.real << " + " << ada.imaginary << "i";

    // what is the difference between the three??
    cout << "First attept: " << endl;
    ada += bee;
    cout << "Second attept: " << endl;
    ada + bee;
    cout << "Third attept: " << endl;
    ada = ada + bee;

    cout << ada << endl;
    return 0;
}
