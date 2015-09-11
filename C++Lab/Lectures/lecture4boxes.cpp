//============================================================================
// Name        : boxes.cpp
// Author      : Stephanie
// Version     :
// Copyright   :
// Description : Shows how to use string streams.
//============================================================================

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void out_basics();
void in_basics();
void trick();

int main() {

	out_basics();
	in_basics();
	trick();

}

void out_basics() {
	// let's make an output string stream
	ostringstream output;

	// and tell a story
	string part1("Once upon a time there lived a cat named Maru.\n");
	string part2("He was an internet phenomenon, with ");
	string part3(" subscribers.\n");
	string part4("But I don't think he cared much about that.\n");
	string part5("No, Maru just really REALLY liked boxes.");

	int subscribers = 478619;

	// now let the story flow into the string stream
	output << part1 << part2 << subscribers << part3 << part4 << part5;

	// and check what it contains!
	cout << "The string stream contains:\n" << output.str() << endl;
}

void in_basics() {
	// let's create a test string
	string test_string("Maru's favourites: 5 M 3.14");

	// and turn it into an input string stream
	istringstream input(test_string);

	// create some variables to hold what's in the string
	string str1;
	string str2;
	int integer;
	char letter;
	double real;

	// and load it up!
	input >> str1 >> str2 >> integer >> letter >> real;

	// print to check
	cout << str1 << " " << str2 << endl;
	cout << "Integer: " << integer << endl;
	cout << "Letter: " << letter << endl;
	cout << "Real number: " << real << endl;
}

void trick() {
	cout << "Tell your own Maru story!" << endl;

	// Remember the problem where >> stops reading when it sees whitespace?
	// We can work around that very easily with string streams.

	ostringstream my_buffer; // this is where we'll keep adding pieces of string
	string temp; // this is where we'll load up space-separated words

	// the while loop will stop when it reaches end-of-file (CTRL + D)
	while ( cin >> temp ) {
		my_buffer << temp << " ";
	}

	cout << "You wrote: \n" << my_buffer.str() << endl;
}
