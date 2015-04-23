#include <iostream>
using namespace std;

/**********************************************************/
/**** Lecture 10 - Templates ****/
/**********************************************************/


/*
 Templates are a feature in C++ that allows generic programming:

 - using types that will be specified later.
 - still, by "later", we don't mean at runtime...
 - "later" = compile time, when an object is instantiated,
 or when a function is called
 (rather than inside function/class definition)

 Templates allow you to:
 - pass types as arguments
 - delay type checking
 - pass constant values as arguments: compile time computation

 This is reminiscent of Java generics, but it is far from that!
    - Java gave up on templates
    - Java introduced (only later!) "wrappers for casting objects" with the
	  same syntax as C++ templates.
 */


template <int NR, int NC>
class Matrix;

template <int N>
class Vector;

template <int NR, int NC>
Vector<NR> multiply(const Matrix<NR, NC>& m, const Vector<NC>& v);


// N - size of vector
template <int N>
class Vector {
public:
    Vector() { data = new double[N]; }

    Vector(const Vector<N>& other) {
        data = new double[N];
        for(int gh = 0; gh < N; gh++)
            data[gh] = other.data[gh];
    }

    ~Vector() { delete [] data;}

    int size() const {return N;}
    double& elem(int i) const {return data[i];}

private:
    double* data;
};

// NR - number of rows, NC - number of columns
template <int NR, int NC>
class Matrix {
public:
    Matrix() {
        data = new double*[NR];
        for (int gh = 0; gh < NR; gh++) {		// instantiating a 2D matrix
            data[gh] = new double[NC];
        }
    }
    ~Matrix() {
        for (int gh = 0; gh < NR; gh++) {
            delete [] data[gh];
        }
        delete [] data;
    }

    int rows() const {return NR;}
    int cols() const {return NC;}
    double& elem(int i, int j) const { return data[i][j]; }

    Vector<NR> operator()(const Vector<NC>& v) const {		// which const does what? can the first const make a non-const const?
        return multiply(*this, v);
    }
private:
    double** data;
};


template <int R, int C>
Vector<R> multiply(const Matrix<R,C>& m, const Vector<C>& v) {
    Vector<R> r;
    for (int gh = 0; gh < m.rows(); gh++) {
        r.elem(gh) = 0;
        for (int hov = 0; hov < m.cols(); hov++) {
            r.elem(gh) += m.elem(gh,hov) * v.elem(hov);
        }
    }
    return r;
}




int main0() {
    Vector<3> v1;
    Vector<2> v2;
    Matrix<4,3> m;
    Vector<4> v3 = multiply(m,v1); //valid

    m(v1); //valid as well
    //m(v2); // invalid AND does not compile	- bc of improper dimensions

    int x = 5+3;

    Vector<8-4*3+2> v4;// = v3; //valid!
    const int z = 4;
    Vector<z> v5 = v3; //valid!
    return 0;
}


/* Example 2: Compile time computation*/

template <int R>
class Circle {
    const double PI = 3.14;
public:
    const double area = PI * R * R;
    const double circ = 2 * PI * R;
};

class CircleOfRadius3 {
    const double PI = 3.14;
public:
    const double area = 28.13;
    const double circ = 19.32;
};

int main1() {
    Circle<3> c;
    Circle<5> c2;
    //c2 = c;
    Circle<7> c3;
    cout << c.area;
    return 0;
}




/*
 Riddles in the dark:

 Three programming languages were sitting in an old Indian temple.
    - Java (always telling the truth), cuz "If you tell the truth, you don't have to remember anything."
    - C (always lying), cuz "A liar needs a good memory"
    - C++ (sometimes lying), cuz "The truth will set you free, but first it will piss you off."

 A visitor
    - asked the one on the *left*: "Who is sitting *next* to you?"
            "JAVA" she answered.
    - Then she asked the one in the *middle*: "Who are you?"
            "C++!"
    - Lastly, she asked the one on the *right*: "Who is your *neighbor*?"
            "C" she replied.

    Who is who?!?

    L		M		R
    C++		C		Java


 */




/* Containers: taking abstraction to another level
 - how does vector<int> and vector<double> and vector<list<int>> work??
 - is it a C++ standard library construct? can we do the same??
 - we NEED to make have the type of elements in the container come as input
 */

/* Non-generic implementation for Stack of doubles */

class stack_silly {
private:
    double* storage;
    int size;
    int top;
public:
    stack_silly(int n=100);
    ~stack_silly();

    double pop();
    void push(double);

};



/* What if I want a stack of Matrices? Generic programming!*/

template <typename T>
class Stack {
private:
    T* storage;
    int size;
    int top;
public:
    Stack(int n=100) {
        storage = new T[n];
        size = n;
        top = -1;
    }
    ~Stack() {
        delete [] storage;
    }

    T pop() {
        if (top >= 0) {
            return storage[top--];			// with top declared as -1, we can start from the back and go backwards!!
        }else return 0;
    }

    void push(T);

};

template<typename T>
void Stack<T>::push(T x) {
    if (top >= size-1) {
        T* new_storage = new T[2*size];
        for (int gh=0; gh<size; gh++) {
            new_storage[gh] = storage[gh];
        }
        delete [] storage;		// notice the []
        storage = new_storage;	// does deleting it still let the var name exist?
    }
    storage[++top] = x;			// do we need to do ++ in prefix?
}



#include <string>

int main() {

    Stack<string> sstack;
    sstack.push("world");
    sstack.push("hello");
    cout << sstack.pop() << endl; // Print hello

    Stack<Matrix<5, 6>> stackOfMatrices;

    return 0;
}



/*
 Class templates: these are *instantiated* : template code is generated on demand

 *CODE ON DEMAND*

 Stack<int> istack;		// Generates code for integer stack
 Stack<double> istack;	// Generates code for double stack

 - if you don't declare a Stack<Matix>, no code is generated for this specific type!!!

 - generates classes as demanded at COMPILE TIME
 */


/* Algorithms on containers : simplified typechecking */



template <typename C, typename P>
int count(const C& c, P pred) {
    int cnt = 0;
    for(const auto& x : c) {	//we don't know if this is a container!
        if(pred(x)) ++cnt;		//we don't know if pred returns a boolean!
    }
    return cnt;
}


template <int N>
bool less_than(int z) { return z < N; }

bool less_than_4(int z) { return z < 4; }


template <typename T>
class Less_than {
    const T val; //val to compare against
public:
    Less_than(const T& v) : val(v) {}

    bool operator()(const T& x) const { return x < val; } // call operator
};


#include <list>

int main4() {
    list<int> l;
    l.push_back(3);
    l.push_back(5);
    l.push_back(6);
    l.push_back(10);

    cout << "There are " << count(l,less_than<4>) << " numbers less than 4 in l" << endl;
    cout << "There are " << count(l,less_than<7>) << " numbers less than 7 in l" << endl;


    list<string> l2;
    l2.push_back("3");
    l2.push_back("5");
    l2.push_back("6");
    l2.push_back("10");
    cout << "-------------------" << endl;
    cout << "There are " << count(l, Less_than<int>{4}) << " numbers less than 4 in l" << endl;	// notice syntax: classname<T>{arg}
    cout << "There are " << count(l, Less_than<int>{7}) << " numbers less than 7 in  l" << endl;

    cout << "There are " << count(l2, Less_than<string>{"4"}) << " strings less than 4 in l2" << endl;
    cout << "There are " << count(l2, Less_than<string>{"7"}) << " strings less than 7 in l2" << endl;
    cout << "-------------------" << endl;

    return 0;
}

/* Templates: other aspects
 - By default, the full template definition must be accessible from any compilation unit (source file) that uses it.
 - Often, this means the entire template definition is placed in a ".h" file.
 - This may expose the implementation, or require extra information to be included during compilation.

 - Inheritance is not preserved across templates:	<--- !!!!!!!!!

 template <typename T> class A { ... };

 class B {  ...  };
 class C : public B {  ...  };

 int main5() {
 B b;
 C c;
 A<B> ab;
 A<C> ac;
 b = c; // legal, as B is derived from C
 ab = ac; // error!
 return 0;
 }

 */



/*******************************************************/
// Assigned readings
// * Templates: http://www.cplusplus.com/doc/oldtutorial/templates/
