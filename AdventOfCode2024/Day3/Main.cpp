#include <iostream>
#include "Day3.hpp"

using namespace std;

int main() {
	const string filename = "Input.txt";
	int addAllMultiplication = Day3::addMultiplicationInCorruptedFile(filename);
	cout << "In the corupted file " << filename << ", adding all multiplication have a total of " << addAllMultiplication << endl;
	int addAllMultiplicationEnabled = Day3::addMultiplicationEnabledInCorruptedFile(filename);
	cout << "In the corupted file " << filename << ", adding all enabled multiplication have a total of " << addAllMultiplicationEnabled << endl;
	return 0;
}