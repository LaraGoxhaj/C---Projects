//TODO : scope! (on twelveDividedByTen and main)
//TODO : functions, order, declaration, definition (on mean and factorial)

#include <iostream>

using namespace std;

double twelveDividedByTen = 1.2; // Global scope

long factorial(int);
double mean(double[], int);


int main () {
	int fivePlusSome = 5; // Local scope
	// Declare ada in statement scope
	for (int ada = 0; ada < fivePlusSome; ada++) {
		// do something silly
		fivePlusSome = fivePlusSome + ada * twelveDividedByTen;
	}
	// ada is now undefined
	fivePlusSome = fivePlusSome + twelveDividedByTen;
	cout << factorial(10) << endl;
	return 0;
}


/* Calculate the mean of an array */
double mean(double data[], int n) {
	double sum = 0.0; // Initialization if (n != 0) return 0.0;
	for (int ada = 0; ada < n; ada++) {
		sum += data[ada];
	}
	return sum / n;
}

int x; //global  scope

/* Impractical recursive factorial */
long factorial(int t) {
	x = t+5;
	if (t <= 1) return 1;
	return t * factorial(t - 1);
}

// what is the value of t before and after a call on factorial?
