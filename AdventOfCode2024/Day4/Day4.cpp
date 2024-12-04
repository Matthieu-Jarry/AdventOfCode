#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Day4.hpp"

using namespace std;

const vector<char> XMAS = { 'X', 'M', 'A', 'S' };
const vector<char> REVERSED_XMAS = [] {
	vector<char> temp = XMAS;
	reverse(temp.begin(), temp.end());
	return temp;
}();

const vector<char> MAS = { 'M', 'A', 'S' };
const vector<char> REVERSED_MAS = [] {
	vector<char> temp = MAS;
	reverse(temp.begin(), temp.end());
	return temp;
	}();

bool checkXMASAndReverse(const vector<char>& currline) {
	return (currline == XMAS || currline == REVERSED_XMAS);
}

bool checkMASAndReverse(const vector<char>& currline) {
	return (currline == MAS || currline == REVERSED_MAS);
}

int findXMASInLine(const vector<char>& currline) {
	if (checkXMASAndReverse(currline)) {
		return 1;
	}
	return 0;
}

int findXMASInLeftDiagonal(const vector<char>& currline, const vector<char>& prev1line, const vector<char>& prev2line, const vector<char>& prev3line) {
	vector<char> newLine;
	int currIndex = currline.size() - 1;
	newLine.push_back(currline.at(currIndex));
	newLine.push_back(prev1line.at(currIndex - 1));
	newLine.push_back(prev2line.at(currIndex - 2));
	newLine.push_back(prev3line.at(currIndex - 3));
	return findXMASInLine(newLine);
}

int findXMASInRightDiagonal(const vector<char>& currline, const vector<char>& prev1line, const vector<char>& prev2line, const vector<char>& prev3line) {
	vector<char> newLine;
	int currIndex = currline.size() - 1;
	newLine.push_back(currline.at(currIndex));
	newLine.push_back(prev1line.at(currIndex + 1));
	newLine.push_back(prev2line.at(currIndex + 2));
	newLine.push_back(prev3line.at(currIndex + 3));
	return findXMASInLine(newLine);
}

int findXMASInTop(const vector<char>& currline, const vector<char>& prev1line, const vector<char>& prev2line, const vector<char>& prev3line) {
	vector<char> newLine;
	int currIndex = currline.size() - 1;
	newLine.push_back(currline.at(currIndex));
	newLine.push_back(prev1line.at(currIndex));
	newLine.push_back(prev2line.at(currIndex));
	newLine.push_back(prev3line.at(currIndex));
	int find = findXMASInLine(newLine);
	return findXMASInLine(newLine);
}

int findXMAS(const vector<char>& currline, const vector<char>& prev1line, const vector<char>& prev2line, const vector<char>& prev3line) {
	char currChar = currline.back();

	if (currChar != XMAS.front() && currChar != XMAS.back()) {
		return 0;
	}

	int nbXMAS = 0;
	size_t currlineSize = currline.size();
	size_t prev3lineSize = prev3line.size();

	if (prev3lineSize == 0 && currlineSize < 4) {
		return 0;
	}
	
	if (currlineSize >= 4) {
		vector<char> subvector(currline.end() - 4, currline.end());
		int find = findXMASInLine(subvector);
		if (find != 0) {
			nbXMAS += find;
		}
	}

	if (prev3lineSize != 0) {
		nbXMAS += findXMASInTop(currline, prev1line, prev2line, prev3line);
		if (currlineSize >= 4) {
			nbXMAS += findXMASInLeftDiagonal(currline, prev1line, prev2line, prev3line);
		}
		if (prev3lineSize - currlineSize >= 3) {
			
			nbXMAS += findXMASInRightDiagonal(currline, prev1line, prev2line, prev3line);
		}
	}

	if (currlineSize >= 4 && prev3lineSize != 0) {
		
	}
	

	return nbXMAS;
}

int findCrossMAS(const vector<char>& topline, const vector<char>& middleline, const vector<char>& bottomline) {
	if (topline.size() == 0 || bottomline.size() < 3) {
		return 0;
	}

	int middleIndex = bottomline.size() - 2;
	if (middleline.at(middleIndex) != 'A') {
		return 0;
	}

	vector<char> leftDiagMas, rightDiagMas;

	leftDiagMas.push_back(topline.at(middleIndex + 1));
	leftDiagMas.push_back(middleline.at(middleIndex));
	leftDiagMas.push_back(bottomline.at(middleIndex - 1));

	rightDiagMas.push_back(topline.at(middleIndex - 1));
	rightDiagMas.push_back(middleline.at(middleIndex));
	rightDiagMas.push_back(bottomline.at(middleIndex + 1));

	if (checkMASAndReverse(leftDiagMas) && checkMASAndReverse(rightDiagMas)) {
		return 1;
	}
	return 0;
}

int Day4::findXMASInFile(const string& filename) {
	int nbXMAS = 0;
	fstream infile(filename);
	string line;
	vector<char> currline, prev1line, prev2line, prev3line;

	if (!infile) {
		cerr << "Error: Unable to open file " << filename << endl;
		return -1;
	}
	int lineIndex = 1;
	while (getline(infile, line)) {
		istringstream iss(line);
		currline.clear();
		char currChar;

		while (iss >> currChar) {
			currline.push_back(currChar);
			nbXMAS += findXMAS(currline, prev1line, prev2line, prev3line);
		}

		prev3line = prev2line;
		prev2line = prev1line;
		prev1line = currline;
	}

	infile.close();

	return nbXMAS;
}

int Day4::findCrossMASInFile(const string& filename) {
	int nbCrossMAS = 0;
	fstream infile(filename);
	string line;
	vector<char> topline, middleline, bottomline;

	if (!infile) {
		cerr << "Error: Unable to open file " << filename << endl;
		return -1;
	}
	int lineIndex = 1;
	while (getline(infile, line)) {
		istringstream iss(line);
		bottomline.clear();
		char currChar;

		while (iss >> currChar) {
			bottomline.push_back(currChar);
			nbCrossMAS += findCrossMAS(topline, middleline, bottomline);
		}

		topline = middleline;
		middleline = bottomline;
	}

	infile.close();

	return nbCrossMAS;
}