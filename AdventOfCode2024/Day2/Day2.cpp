#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <deque>
#include <vector>
#include "Day2.hpp"

constexpr auto INCREASING = 1;
constexpr auto DECREASING = -1;
constexpr auto LINEAR = 0;

using namespace std;

static int getDirection(int& prevNum, int& currNum) {
    int direction = LINEAR;

    if (currNum - prevNum > 0) {
        direction = DECREASING;
    }
    else if (currNum - prevNum < 0) {
        direction = INCREASING;
    }
    
    return direction;
}

static vector<vector<int>> generateSubVectorsWithOriginal(const vector<int>& input) {
    vector<vector<int>> result;

    // Include the original vector
    result.push_back(input);

    // Generate sub-vectors excluding one element
    for (size_t i = 0; i < input.size(); ++i) {
        vector<int> subVector;
        for (size_t j = 0; j < input.size(); ++j) {
            if (j != i) {  // Exclude the element at index i
                subVector.push_back(input[j]);
            }
        }
        result.push_back(subVector);
    }

    return result;
}

static bool isSafe(const vector<int>& list) {
    int prevNum, currNum;
    int directionGen;
    int directionCur;
    bool validDistance, validRow = true, firstNum = true;
    int i = 1;
    prevNum = list.at(0);
    while (i < list.size() && validRow) {
        currNum = list.at(i);
        int distance = abs(currNum - prevNum);

        if (firstNum) {
            directionGen = getDirection(prevNum, currNum);
            firstNum = false;
        }

        directionCur = getDirection(prevNum, currNum);
        validDistance = (distance >= 1 && distance <= 3);

        validRow = (validDistance && (directionGen == directionCur));
        prevNum = currNum;
        i++;
    }

    return validRow;
}

int Day2::getNbReportSafe(const string& filename) {
    int nbReportSafe = 0;
    string line;
    vector<int> list;
    ifstream infile(filename);

    if (!infile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return -1;
    }

    while (getline(infile, line)) {
        istringstream iss(line);
        list.clear();
        int currNum;
        bool safe = false;
        while (iss >> currNum) {
            list.push_back(currNum);
        }
        if (isSafe(list)) {
            nbReportSafe++;
        }
    }

    infile.close();
    return nbReportSafe;
}

int Day2::getNbReportSafeRemoveOneBadLevelNotOptimize(const string& filename) {
    int nbReportSafe = 0;
    string line;
    deque<int> dequeReport;
    vector<int> list;

    ifstream infile(filename);

    if (!infile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return -1;
    }

    while (getline(infile, line)) {
        istringstream iss(line);
        list.clear();
        int currNum;
        bool safe = false;
        while (iss >> currNum) {
            list.push_back(currNum);
        }
        std::vector<std::vector<int>> subVectors = generateSubVectorsWithOriginal(list);

        for (const auto& vec : subVectors) {
            safe = isSafe(vec);
            if (safe) {
                nbReportSafe++;
                break;
            }
        }
    }
    return nbReportSafe;
}
