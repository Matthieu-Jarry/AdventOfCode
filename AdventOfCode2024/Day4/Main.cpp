#include <iostream>
#include "Day4.hpp"
using namespace std;

int main() {
	const string filename = "Input.txt";
	int nbXMAS = Day4::findXMASInFile(filename);
	cout << nbXMAS << " XMAS find in the file " << filename << endl;

	int nbCrossMAS = Day4::findCrossMASInFile(filename);
	cout << nbCrossMAS << " Cross MAS find in the file " << filename << endl;

	return 0;
}