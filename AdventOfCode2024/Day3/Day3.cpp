#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "Day3.hpp"

using namespace std;

int Day3::addMultiplicationInCorruptedFile(const string& filename) {
    const regex pattern(R"(mul\((\d+),(\d+)\))");
    smatch match;
    int addAllMultiplication = 0;
    ifstream infile(filename);
    string line;

    if (!infile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return -1;
    }

    while (getline(infile, line)) {
        string::const_iterator searchStart(line.cbegin());

        while (regex_search(searchStart, line.cend(), match, pattern)) {
            int x = stoi(match[1].str());
            int y = stoi(match[2].str());
            addAllMultiplication += x * y;
            searchStart = match.suffix().first;
        }
    }

    infile.close();
    return addAllMultiplication;
}

int Day3::addMultiplicationEnabledInCorruptedFile(const string& filename) {
    const regex mulPattern(R"(mul\((\d+),\s*(\d+)\))");
    const regex doPattern(R"(do\(\))");
    const regex dontPattern(R"(don't\(\))");
    smatch match;
    int addAllMultiplication = 0;
    bool enabled = true;
    ifstream infile(filename);
    string line;

    if (!infile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return -1;
    }

    while (getline(infile, line)) {
        string::const_iterator searchStart(line.cbegin());

        while (regex_search(searchStart, line.cend(), match, regex(R"(do\(\)|don't\(\)|mul\((\d+),\s*(\d+)\))"))) {
            string matchedStr = match.str();

            if (regex_match(matchedStr, doPattern)) {
                enabled = true;
            }
            else if (regex_match(matchedStr, dontPattern)) {
                enabled = false;
            }
            else if (enabled && regex_match(matchedStr,mulPattern)) {
                int x = stoi(match[1].str());
                int y = stoi(match[2].str());
                addAllMultiplication += x * y;
            }
            searchStart = match.suffix().first;
        }
    }

    infile.close();
    return addAllMultiplication;
}