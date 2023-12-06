

#ifndef TS_SOLUTION_H
#define TS_SOLUTION_H
#include <vector>
#include "../structures/Graph.h"
#include <iostream>

using namespace std;


class Solution {
private:
     int findNearestCity(int currentCity, const Graph& graph, const std::vector<bool>& visited);

public:
    vector <int> path;
    int cost = 0;


    int calculateCost(const Graph& graph);
    void printSolution();

    static Solution greedySolution(const Graph& graph);

};


#endif //TS_SOLUTION_H
