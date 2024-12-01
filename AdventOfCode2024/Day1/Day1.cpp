#include <vector>
#include "Day1.hpp"

using namespace std;

int Day1::distanceBetweenTwoVector(vector<double>& vec1, vector<double>& vec2) {
    int distance = 0;
    int i = 0;

    while (i < vec1.size() && i < vec2.size()) {
        int min = vec1.at(i);
        int max = vec2.at(i);
        int tmp;

        if (min > max) {
            tmp = max;
            max = min;
            min = tmp;
        }
        distance += max - min;
        i++;
    }

    return distance;
}

int Day1::similarityBetweenTwoVector(vector<double>& vec1, vector<double>& vec2) {
    int similarityScore = 0;

    for (double value1 : vec1) {
        int numberOfApperance = 0;
        int i = 0;
        while (i < vec2.size() && vec2.at(i) <= value1) {
            if (vec2.at(i) == value1) {
                numberOfApperance++;
            }
            i++;
        }
        similarityScore += value1 * numberOfApperance;
    }
    return similarityScore;
}