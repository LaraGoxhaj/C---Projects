//============================================================================
// Name        : lannisters.cpp
// Author      : Stephanie
// Version     :
// Copyright   :
// Description : Showing some manipulators & how to make your own
//============================================================================

#include <iostream>
#include <string>
#include <iomanip> // for parametrized manipulators (i.e. take an argument)

using namespace std;

void basic_examples();
ostream& bell(ostream&);

int main() {
	// basic_examples();

	cout << "\nPie is ready." << bell << endl;

}

void basic_examples() {

	cout << "The Lannisters send their regards.\nAnd pie." << endl;
	cout << "How many pies do they send?" << endl;

	int n_pies;
	cin >> n_pies;

	// setw lets you decide how many characters should be streamed
	cout << "(decimal)" << setw(20) << n_pies << endl;
	// use hex, dec, oct to change base
	cout << "(hex)" << hex << setw(24) << n_pies << endl;
	// you can also use setbase, which needs <iomanip>
	cout << "(oct)" << setbase(8) << setw(24) << n_pies << endl;
	// base changes are sticky manipulators, but not width settings
	cout << dec;


	double pie = 3.1415926536;
	cout << "The pie can be more or less precise." << endl;

	cout << fixed; // uses fixed-point notation (i.e. precision = # decimals)

	for (int p = 0; p <= 10; ++p) {
		cout << setprecision(p) << pie << endl;
	}

}

// defining your own manipulator!
// pretty simple: take a stream, do something to it, return it

ostream& bell( ostream& output ) {
	return output << '\a'; // makes system beep :)
}

