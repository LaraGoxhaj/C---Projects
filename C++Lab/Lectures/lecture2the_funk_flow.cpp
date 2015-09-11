/*
 * the_funk_flow.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: gcoman
 */

#include <iostream>

using namespace std;

int theFunkFlow() {

	/***************
	 IF : statement
	****************/

	bool IRuledTheWorld = (5 < 3);
	if (  IRuledTheWorld /*boolean, int value*/ ) {
		/* TRUE_stmtList */
		cout << "I'd free all my sons, I love em love em baby";
	} else {
		/* FALSE_stmtLst */
		cout << "I'd teach C++";
	}
	// Only one of the TWO statement lists will be evaluated!
	// bool can only take TWO values

	/******************
 	 SWITCH : statement
	 *******************/

	cout << "How old is Bart? ";
	int response;
	cin >> response;
	// IF works with booleans only: two possible cases!
	switch ( response /* int,char value, enum */ ) {
	case 10:
		cout << "Ay, caramba! " << endl;
		break; //VERY IMPORTANT
	case 8:
	case 9:
	case 11:
	case 12:
		cout << "*facepalm*";
		break; //VERY IMPORTANT
	default:
		cout << "Shut up, Lisa!" << endl;
	}

	// The switch keeps going until it hits a break!!!

	/******************
 	 WHILE : statement
	 *******************/
	bool myGuitarGentlyWeeps = true;
	int boredom = 0;
	while ( myGuitarGentlyWeeps /*boolean*/ ) {
		cout << "Sing it Georgie Boy" << endl;
		boredom++;
		if(boredom > 10) {
			cout << "Shut up, Georgie Boy!....you too, Lisa!" << endl;
			myGuitarGentlyWeeps = false;
		}
	}

	/******************
	 FOR statement : MY FAVOURITE!
	 *******************/
	int multipleOfTwo=0;
	for (int ada = 1 ; ada < 10 ; ++ada ) {
		cout << multipleOfTwo << " ";
		multipleOfTwo += 2;
	}


	/**
	 * There, but try not to use it!
	 * */
	do {
		cout << "I got the funk flow to make your drawers drop slow"
				<< endl;
	}while(true);

	return 0;
}

//Don't forget to mention 'continue' and 'break', Georgie Boy
