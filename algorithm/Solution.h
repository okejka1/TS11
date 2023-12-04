

#ifndef TS_SOLUTION_H
#define TS_SOLUTION_H
#include "vector";
#include "../structures/Graph.h"

using namespace std;
class Solution {
public:
    vector<int> path;
    int cost = 0;
    int calculateCost(Graph &graph);
    void printSolution();
    Solution greedySolution(Graph &graph);
    Solution randomSolution(Graph &graph);

private:
    int findNearestCity(int currentCity, Graph &graph, vector<bool> &visited);
};


#endif //TS_SOLUTION_H
