#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include "Day1.hpp"

using namespace std;

int main() {
    string filename = "input.txt";
    vector<double> column1;
    vector<double> column2;
    double value1, value2;
    int distance = 0;
    int similarityScore = 0;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: unable to open file " << filename << endl;
        return 1;
    }

    while (infile >> value1 >> value2) {
        column1.push_back(value1);
        column2.push_back(value2);
    }

    infile.close();

    sort(column1.begin(), column1.end());
    sort(column2.begin(), column2.end());

    distance = Day1::distanceBetweenTwoVector(column1, column2);
    cout << "Distance between two columns : " << distance << endl;

    similarityScore = Day1::similarityBetweenTwoVector(column1, column2);
    cout << "Similarity score between two columns : " << similarityScore << endl;

    return EXIT_SUCCESS;
}