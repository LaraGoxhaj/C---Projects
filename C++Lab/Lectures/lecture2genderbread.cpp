//============================================================================
// Name        : Lecture.cpp
// Author      : Gheorghe
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;


enum expression {NONE, SOME, MORE};

//declaration
string operator+(expression, expression);


int main() {
	string gheorgheIdentity = (SOME + SOME);
	cout << "Gheorghe identifies as " << gheorgheIdentity << endl;
	return 0;
}


//definition
string operator+(expression womanNess, expression manNess) {
	if(womanNess == manNess) {
		switch(womanNess) {
		case NONE:
			return "genderless";
		case SOME:
			return "two-spirit";
		case MORE:
			return "genderqueer";
		}
	}
	if(manNess == NONE || (manNess == SOME && womanNess == MORE)) {
		return "woman";
	}
	return "man";
}
