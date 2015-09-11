/*********************************/
/**** Lecture 9 - Exceptions ****/
/*********************************/

#include <iostream>

/* Two aspects that one has in C++, but not in Java. Avoid them at all costs!*/

/** Multiple inheritance */

/*
 * multiple inheritance:
    D
   / \
  A   B
   \ /
    C

D = C
well, which C do you want, the B or the A copy?
so you must "cast" (or that's what it's called in c__

remember that we have no pointer or references,
just copies!

you have to do casting to specifically specify which
pointer to d you want

Don't do multiple inheritance - at least not at our level..

just be aware that you can call methods separately
 *
 */


class D {
public:
    int dd;
    void ff() {};
};



class A : public D { // base class 1
    int x;
public:
    void f() {}
};

class B : public D { // base class 2
    int y;
public:
    void f() {} // source of ambiguity
    void g() {}
};


// the dreaded diamond!!!!!
class C : public A, public B { // C inherits from A & B
    int z; // Visible only within C
public: // ..
};


int main2() {
    A a;
    B b;
    C c;
    a = c; // OK
    b = c; // OK
    //D d = c; // NOT OK - from which C??? the one that inherits from A, or from B?? We don't know!
    D d1 = (A) c; // OK
    D d2 = (B) c; // OK

    //c = a; // Error
    A *pa = &c;
    B *pb = &c;
    //D *pd = &c; //NOT OK
    D* pd1 = (A *) &c; // OK
    D* pd2 = (B *) &c; // OK

    //In general , (int) pa != (int) pb
    // This is because the data of c is organized as follows: | D | A | D | B | C
    // data of class A, followed by data of class B, followed by data of class C
    // taking the address of c either as type pointer to A or pointer to B, it will
    // get the address at the memory of c associated with class A, resp. class B



    // c.f(); // does not compile: which f are we calling?
    // so we have to specify as follows (notice this syntax, it's a bit weird)
    c.A::f();
    c.B::f();

    return 0;
}





/* gotos */


#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

bool f() {
    int *pc = NULL;
    FILE *fp = NULL;
    pc = (int *) malloc(sizeof(int) * 100);
    if (pc == NULL) {
        goto error; }		// please don't use goto's in your code, you'll get automatic 0's...
    fp = fopen("outfile", "w");
    if (fp == NULL) {
        goto error; }
    // ...
    free(pc); fclose(fp);
    return true;
error:
    if (pc != NULL) free(fp);
    if (fp != NULL) fclose(fp);
    // ...
    return false;
}

/* [DIRECTLY PRIOR TO REWRITING A FOR LOOP USING GOTOS]
 * don't do this! is a main cause of errors!
 * (what?)
 * Please don't submit code with gotos for this class - instant 0
 *
 * People prefer exceptions to gotos bc they actually unwind the stack (gotos don't)
 */

//rewrite a for loop using gotosr
void z() {
    for (int ada = 0; ada < 3; ada++) {
        int bee = ada + 4;
        std::cout << bee;
    }



    {
        int ada=0;
    loopStarts:
        if(ada < 3) {
            int bee = ada + 4;
            std::cout << bee;
            ada++;
            goto loopStarts;
        }
    }

}



/* EXCEPTIONS */

/**
 - HANDLE exceptional conditions
 - PASS error information
 - GIVE control to a caller when no action has any meaning locally
 - STOPS the use of print messages and gotos for debugging
 **/

// Java only compiles if you handle al possible exceptions that can be thrown;
// c++ doesn't have that (?)

/* You can rethrow an exception!
 * when throw exception, put const in front to make sure it doesn't change
 * and with references
 * good habit to do
 *
 * always keep with the least general first and move on to the more general
 *
 * try to catch by reference, it's the norm
 * make sure exceptions are const when catch them so rethrow
 * will maintain the error
 *
 * be aware that you can import std::except
 * try to use these and only create your own exceptions if what you're using doesn't satisfy
 * because people already understand these excpetions well
 *
 */


/** Syntax : try, catch, throw **/

#include <iostream>
#include <string>

using namespace std;

void giveOscar(string name) { // etc.
    if ( name == "Tom Cruise" /* something goes wrong */) { throw 2.0; }
    cout << "YAY for the winner: " + name << endl;
    // ... more code ...
}


int main() {
    try {
        // ...
        giveOscar("Idris Elba");
        giveOscar("Tom Cruise");
        //..
        //..
    }
    catch (double code) { // Handle int exceptions
        std::cerr << "Caught exception " << code << std::endl;
    }
    catch (...) { // Default handler
        std::cerr << "Caught unknown exception" << std::endl; }
}


/** C++ vs. Java
 - C++ has no *finally* block
 - C++ can throw any type
 - C++ methods are not required to have throw specifications - if specified, other types will exit the program upon being thrown
 - in C++, only give a name to the type of the exception if the data will be used.
 **/




/**
 Exceptions "unwind" the stack!
 - all objects going out of scope are destroyed.
 - objects created with new will NOT be destroyed (they are created on the heap)
 **/

#include <string>

void gg() {
    // ...
    int* p = new int[100];
    string s("silly string that gets destroyed without being used");
    throw 13; // s is destroyed, p is destroyed, but not the data p points to!
    // ^ so is this a memory leak??
    // ... more code that never gets executed
    string oscarWinner;
    oscarWinner = "Tom Cruise";
    cout << "Congratulations " + oscarWinner;

}

void fff() {
    try {
        gg();

    }
    catch (int& e) { // Will be caught here...
        std::cerr << "fff " << e << std::endl;
        e = 15;
        throw e;
    }
}


/* RIDDLES IN THE DARK:
 "What is a bell that does not ring, yet it's knell makes the angels sing?"
 */



//alternative to fff()
void ffff() try {
    gg();
}
catch (int e) { // Will be caught here...
    std::cerr << "fff " << e << std::endl;
}


int main3() {
    try {
        fff();
    }
    catch (const int& e) { // ...not here.
        std::cerr << "main " << e << std::endl;
    }
    return 0;
}

/** Re-throw
     - If your exception handler cannot completely
     handle the exception, it can Ã¢â‚¬Å“re-throwÃ¢â‚¬Â
     the exception for the benefit of a caller.
     - The exception will be passed upwards.
     If you the exception is received by
     non-const reference or pointer, any modification
     will be passed to the next handler.
**/


/**
The order of exception handlers matters. When an exception occurs, C++ scans through the list of eligible exception handlers and
selects the first one that is compatible. Therefore we often list catch blocks in order of increasing generality:
**/

int main4() {
    try {
        fff();
    }
    catch(const C& c ) { /* ... */ } // Least general
    catch(const A& b ) { /* ... */ } // More general
    catch(const B& b ) { /* ... */ } // More general
    catch ( ... ) { /* ... */ } // Most general
    return 0;
}

    /**
     In hierachical classes, throwing/catching is equivalent to calling a method
     - carefully choose the type of the parameters

     Passing exceptions by pointers is somewhat dangerous,
     as it may be unclear when and if to delete the exception.
     **/


    /**
     EXCEPTION GUIDELINES

     - in large programs, you should define a set of exception classes
     (even though C++ allows you to throw any type
     - catch by reference is the norm
     - don't throw exceptions in a destructor
     // ^ why not???
      * unless a user provided destructor has an explicit exception specification, one will
      * be added implicitly, matching the one that an implicit destructor for the type would
      * have received
      * Furthermore when an exception is throw, stack unwinding will call the destructors of
      * all objects with automatic storage duration still in scope up to the location where the
      * exception is eventually caught. The porgram will immediately terminate should another
      * exception be thrown from a destructor of one of these objects.
     - standard library methods may throw a number of possible exceptions.
     These are in <stdexcept>
     - The "root" exception class is std::exception
     - It is common to have new exceptions inherit from std::runtime error

     - "Exception safe" code:
     - Restore modified structures to standard values
     - Release resources
     **/






    /*******************************************************/
    // Assigned readings

    // * Exceptions :   http://www.cplusplus.com/doc/tutorial/exceptions/
    //                  http://www.cplusplus.com/reference/exception/exception/
    // * Operator overloading : http://en.cppreference.com/w/cpp/language/operators


