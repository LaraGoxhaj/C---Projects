//============================================================================
// Name        : files.cpp
// Author      : Stephanie
// Version     :
// Copyright   :
// Description : Shows how to use file streams.
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <time.h> // can use to time stuff

using namespace std;

// Remember the difference between \n and endl?
// When you flush a buffered stream can affect the time of operations,
// especially for I/O with files.

time_t print_with(ifstream*, ofstream*, bool);

int main() {

	ofstream wri("numbers.txt");
	for (int i = 0; i < 1000000; i++) {
		wri << i << "\n";
	}

	wri.close();

	// get ourselves the files to read & write
	ifstream to_read("numbers.txt");
	ofstream dump1("dump1.txt");
	ofstream dump2("dump2.txt");

	// print each line with \n, flushing only when buffer is full or program ends
	time_t n_time = print_with(&to_read, &dump1, true);
	dump1.close();

	// rewind stream to beginning of file
	to_read.clear(); // forget you reached end of file
	to_read.seekg(0); // move to start

	// now do the same with endl (flushing at each line)
	time_t endl_time = print_with(&to_read, &dump2, false);
	dump2.close();

	// don't forget to close all the files!
	to_read.close();

	// compare the results
	cout << "With \\n: " << n_time << endl;
	cout << "With endl: " << endl_time << endl;
	cout << "\\n was " << endl_time/(1.0*n_time) << " times faster than endl." << endl;
}

time_t print_with(ifstream* in, ofstream* out, bool use_n) {
	time_t start = clock();
	string c;
	if (use_n) {
		while ( *in >> c ) {
			*out << c << "\n"; // i.e. do not flush
		}
	}
	else {
		while ( *in >> c ) {
			*out << c << endl; // i.e. << "\n" << flush
		}
	}
	time_t end = clock();
	return (end-start);
}
