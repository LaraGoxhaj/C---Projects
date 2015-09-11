//============================================================================
// Name        : tugofwar.cpp
// Author      : Gheorghe
// Version     :
// Copyright   : don't get high on yo' own supply
// Description :
//============================================================================

#include <iostream>
#include <string>

using namespace std;

int main() {

	string myString = "Love is like a tug of war...It's hard to hold on, but even harder to let go.";
	int tugOfWar, me, you;

	for(tugOfWar = me = you = 0 ; cout << myString << endl, tugOfWar < 5; tugOfWar = me++ + ++you) ;

	return 0;
}
