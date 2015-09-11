// PREPORCESSOR COMMANDS THE COMPILER :
//How should the compiler modify the source file?


#define PI 3.14159265359
#define HASH_TABLE_SIZE 100
#define MYNAME "fred"

// CONVENTION: capital letters!

// more elaborate examples
#define MAX(a,b) ((a < b) ? (b) : (a))
#define SWAP(a,b,type) {type tmp = a; a = b; b = tmp; }

//includes
#include <iostream> // "..." search a bunch of standard directories
#include <sys/stat.h>
#include "myhdr.h" // "..." search in *local* directory first!

// CONVENTION: header files take .h extension


// ifndef
#ifndef PI
#define PI 3.14159265359
#endif



/************/
#define VERSION 5

#if (VERSION >= 2)
// code for version 2 and later
#elif (VERSION >= 1)
// code for version 1
#else
// default code
#endif

/************/
#if __OSTYPE==LINUX
#define USETHREADS 1
#else
#define USETHREADS 0
#endif // __OSTYPE


/**Other pre-proc***********/
#undef PI

#ifndef BLEH
#error You must define BLEH  //error stops compilation!!!
#endif
