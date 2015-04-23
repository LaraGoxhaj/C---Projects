/***********************************************/

/**** Lecture 08 - Classes, OOP and Inheritance ****/


/***********************************************/

/* While this is a totally subjective question, I think the general C++ community
 * prefers not to have this->. Its cluttering, and entirely not needed.
 * Some people use it to differentiate between member variables and parameters.
 * A much more common practice is to just prefix your member variables with
 * something, like a single underscore or an m, or m_, etc.
 * That is much easier to read, in my opinion. If you need this-> to differentiate
 * between variables, you're doing it wrong. Either change the parameter name (from
 * x to newX) or have a member variable naming convention.
 * Consistency is preferred, so instead of forcing this-> on yourself for the few
 * cases you need to differentiate (note in initializer lists this is completely
 * well-defined: x(x), where the member x is initialized by the parameter x), just
 * get better variable names.
 * This leaves the only time I use this: when I actually need the address of the
 * instance, for whatever reason.
 */



// * _Inheritance_ refers to our ability to create a hierarchy of classes, in which derived classes (subclass) automatically
// * incorporate functionality from their base classes (superclass).
// * A derived class inherits all of the data and methods from its base class.
// * A derived class may override one or more of the inherited methods.
// * Most of the utility of classes and objects comes from the creation of class hierarchies.

/* C++ wants you to do private inheritance
 * class Automobile : Vehicule // get compilation error
 * class Automobile : public Vehicle / need the public
 *
 * const string retDes() const // very important - for the method -
 * 		method will be available when you use a method of type vehicle and using const
 *		// if don't add the second const you are removing functionality
 *
 * virtual - creates pointer to a method, and pick which class to use at runtime
 * not using virtual - creates both and picks one classd depending on the description
 *
 * if you want to add a behavior that is default in java, use virtual
 *
 * by default, if you don't say anything, every constructor is implicit
 *
 */

#include <iostream>
#include <math.h>

using namespace std;



class A { // base class
private:
    int x; // Visible only within ’A’
protected:
    int y; // Visible to derived classes
public:
    int z; // Visible globally
    A(); // Constructor
    ~A(); // Destructor
    void f(); // Example method
};

class B : public A { // B is derived from A publicly
private:
    int w; // Visible only within ’B’
public:
    B(); // Constructor
    ~B(); // Destructor
    void g() {
        w = z + y;  // OK
        f();        // OK
        //w = x + 1;  // Error - ’x’ is private to ’B’
    }
};

/*Implementations*/
A::A() {}
A::~A() {}
void A::f() {}
B::B() {}
B::~B() {}


/*****************************************************/
// Public inheritance
// * The use of the *public* keyword is the norm although in some rare circumstances you will use private or protected.
// * If you omit the *public* keyword, inheritance is *private*.


class C {
public:
    void f();
};

class D: C { // D inherits C privately
public:
    void g();
};


int mainCD() {
    C c;
    D d;
    c.f(); // OK
    d.g(); // OK
    //d.f(); // Illegal bc f() is public in C, but D inherits C privately, so does not inherit f()
    return 0;
}

/*Implementations*/
void C::f() {}
void D::g() { f();}

/******************************************************************/

class E {
public:
    void f_call(int x) {
        cout << "E::f_call(" << x << ")\n";
    }
};

class F : public E {
public:
    //overriding
    void f_call(int x) {
        E::f_call(x); // uncomment this to see another example
        cout << "- F::f_call(" << x << ")\n";
    }
};

int mainEF() {
    E e;
    cout << "--------" << endl;
    F f;
    cout << "--------" << endl;
    e.f_call(1);
    cout << "--------" << endl;
    f.f_call(2);
    cout << "--------" << endl;
    return 0;
}

// The main program should print:
// E::f_call(1)
// - F::f_call(2)


/******************************************************************/
/*********     INHERITANCE AND CONSTRUCTORS     ********/


class G {
public:
    G() { cout << "G()\n"; }
    ~G() { cout << "~G()\n"; }
    void f_call() { cerr << "G::f_call()\n"; } // Not special
};

class H: public G {
public:
    H() { cout << "- H()\n"; }
    H(int x) { cout << " H(int)\n "; }
    ~H() { cout << "- ~H()\n"; }
    void f_call() { cerr << "- H::f_call()\n"; }
};

int mainGH() {
    G g;
    cout << "--------" << endl;
    g.f_call();
    cout << "--------" << endl;
    H h;
    cout << "--------" << endl;
    H hh(3);
    cout << "--------" << endl;
    h.f_call();
    cout << "--------" << endl;
    return 0;
    //destructors
}


// this main function should produce the following output
//G()
//--------
//G::f_call()
//--------
//G()
//- H()
//--------
//- H::f_call()
//--------
//- ~H()			// the destructors are called automatically
//~G()
//~G()


/***************************/
// Implicit vs. explicit constructor invocation

class I {
public:
    I() { cout << "I()\n"; }
    I(int x) { cout << "I("<< x << ")\n"; }
    ~I() { cout << "~I()\n"; }
    void f_call() { cerr << "I::f_call()\n"; } // Not special
};

class J: public I {
public:
    //J() { cout << "- J()\n"; }
    //J(int x=2) { cout << "- J("<< x << ")\n"; }
    explicit J(int x=2) : I(x) { cout << "- J("<< x << ")\n"; }
    ~J() { cout << "- ~J()\n"; }
    void f_call() { cerr << "- J::f_call()\n"; }
};


int main() {
    J k;
    J j(3);
    //J jj = 3; //error, unless we remove the explicit in front of the constructor
    return 0;
}

/*
 * In C++, a constructor with only one required parameter is considered an implicit conversion function.
 * It converts the parameter type to the class type. Whether this is a good thing or not depends on the
 * semantics of the constructor. For example, if you have a string class with constructor String(const char* s),
 * that's probably exactly what you want. You can pass a const char* to a function expecting a String,
 * and the compiler will automatically construct a temporary String object for you.
 * On the other hand, if you have a buffer class whose constructor Buffer(int size) takes the size of the buffer
 * in bytes, you probably don't want the compiler to quietly turn ints into Buffers. To prevent that, you declare
 * the constructor with the explicit keyword:
 * 		class Buffer { explicit Buffer(int size); ... }
 * That way,
 * 		void useBuffer(Buffer& buf);
 * 		useBuffer(4);
 * becomes a compile-time error. If you want to pass a temporary Buffer object, you have to do so explicitly:
 * 		useBuffer(Buffer(4));
 * In summary, if your single-parameter constructor converts the parameter into an object of your class, you probably
 * don't want to use the explicit keyword. But if you have a constructor that simply happens to take a single
 * parameter, you should declare it as explicit to prevent the compiler from surprising you with unexpected conversions.
 */



/*********************************************/
// SHAPE EXAMPLE

class shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;

};


class polygon : public shape {
protected:
    int nsides;         // Number of sides
    double *lengths;    // Lengths of each side public: !!!!!! (shouldn't it be private?)

    polygon(double width=1.0, double height=1.0);
    polygon(int n, double *len);
    ~polygon() { delete [] lengths; }
public:
    double perimeter() const { // Override base class
        double p = 0.0;
        for (int i = 0; i < nsides; i++) p += lengths[i];
        return (p);
    }
};


class rectangle: public polygon {
public:
    // Constructor just calls the base class
    rectangle(double width, double length) : polygon(width, length) { }
    // Override base class
    double area() const { return lengths[0] * lengths[1];}
};


#define PI 3.14159

class ellipse: public shape {
protected:
    double semimajor, semiminor;
public:
    ellipse(double smj=1.0, double smn=1.0) {
        semimajor = smj;
        semiminor = smn;
    }

    double area() const {
        return PI * semimajor * semiminor;
    }

    double perimeter() const {
        return 2 * PI * sqrt(semimajor * semimajor + semiminor * semiminor);
    }
};


class circle : public ellipse {
public:
    circle(double r = 1.0) : ellipse(r, r) { }
    // Don’t override area(), but provide perimeter()
    double perimeter() const {
        return 2 * PI * semimajor; // ‘‘semimajor’’ is protected
    }
};


void printShapeInfo(shape& s) {
    cout << s.area() << " " << s.perimeter() << endl;
}

int mainShape() {
    circle c1(1);
    rectangle r1(1, 1);
    cout << c1.area() << " " << c1.perimeter() << endl;
    cout << r1.area() << " " << r1.perimeter() << endl;
    return 0;
}


// This method should return:
//3.14159 6.28318
//1 4



/**********************************************************/

int mainShape2() {
    circle c1(1);
    rectangle r1(1, 1);
    cout << c1.area() << " " << c1.perimeter() << endl;
    cout << r1.area() << " " << r1.perimeter() << endl;
    shape *sh = &c1;
    //ellipse *e1 = sh; //does not compile!		!!!!!!!!!!!!!!!!!!!!
    cout << "----------------" << endl;
    cout << sh->area() << " " << sh->perimeter() << endl;
    sh = &r1;
    cout << "----------------" << endl;
    cout << sh->area() << " " << sh->perimeter() << endl;
    return 0;
}







/**Method implementation**/

polygon::polygon(double width, double height) {
    nsides = 4;
    lengths = new double[4];
    lengths[0] = width;
    lengths[1] = height;
    lengths[2] = width;
    lengths[3] = height;
}

polygon::polygon(int n, double *len) {
    nsides = n;
    lengths = len;
}


/*******************************************************/
// Assigned readings

// * Inheritance: http://www.cplusplus.com/doc/tutorial/inheritance/


