//============================================================================
// Name        : extraction.cpp
// Author      : Stephanie
// Version     :
// Copyright   :
// Description : Showing basics of input streams
//============================================================================

#include <iostream>
#include <string>

using namespace std;

void first_attempt();
void second_attempt();
void useful();

int main() {
	// first_attempt();
	// second_attempt();
	// third_attempt();
	// useful();
}

// If you give an answer with more than two words... what happens?
void first_attempt() {
	cout << "Location?" << endl;

	string location;
	cin >> location;
	cout << location << endl;
}

void second_attempt() {
	cout << "Try again... Building, then room." << endl;

	string building;
	string room;

	cin >> building >> room;


	cout << "Beginning extraction from " << building << " " << room << "." << endl;
}

void useful() {

	// cin vs cin.getline
	// we have seen that cin stops reading when it sees whitespace
	// cin.getline stops reading when line ends or it runs out of space
	char buffer[80];
	cout << "Write a sentence:" << endl;
	cin.getline(buffer, 80);
	cout << "You said:\n" << buffer << endl;

	// cin.get
	cout << "Give a character twice. The first time, it will be saved in a char, the second, in an int." << endl;
	char c = cin.get();
	int i = cin.get();
	cout << "char: " << c << endl;
	cout << "int: " << i << endl;


}
