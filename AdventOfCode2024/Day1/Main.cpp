#include <iostream>
#include <vector>
#include <fstream>
#include "triRapide.hpp"
#include "Day1.hpp"

using namespace std;
using namespace TriRapide;

int main() {
    string filename = "input.txt";
    vector<double> column1;
    vector<double> column2;
    double value1, value2;
    int distance = 0;
    int similarityScore = 0;

    ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: unable to open file " << filename << std::endl;
        return 1;
    }

    while (infile >> value1 >> value2) {
        column1.push_back(value1);
        column2.push_back(value2);
    }

    infile.close();

    quickSort(column1);
    quickSort(column2);

    distance = Day1::distanceBetweenTwoVector(column1, column2);
    cout << "Distance between two columns : " << distance << endl;

    similarityScore = Day1::similarityBetweenTwoVector(column1, column2);
    cout << "Similarity score between two columns : " << similarityScore << endl;

    return EXIT_SUCCESS;
}