#include <iostream>
#include "Day2.hpp"
using namespace std;

int main() {
	const string filename = "Input.txt";
	int nbReportSafe = Day2::getNbReportSafe(filename);
	cout << nbReportSafe << " reports are safe" << endl;

	int nbReportSafeRemoveOneBadLevel = Day2::getNbReportSafeRemoveOneBadLevelNotOptimize(filename);
	cout << nbReportSafeRemoveOneBadLevel << " reports are safe with the Problem Dampener" << endl;
	
	cin.ignore();
	return EXIT_SUCCESS;
}