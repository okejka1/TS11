

#ifndef TS_TABUSEARCH_H
#define TS_TABUSEARCH_H


#include <vector>
#include "../structures/Graph.h"
#include "../structures/TabuList.h"
using namespace std;

class TabuSearch {

public:
    explicit TabuSearch(Graph &graph);
    ~TabuSearch();


// fields
    TabuList tabuList;
    Graph g;
    int numOfCities;
//    int *currentSolution;
//    int *bestSolution;
//    int *neighbourSolution;
    vector<int> currentSolution;
    vector<int> bestSolution;
    vector<int> neighbourSolution;

    int currentSolutionCost;
    int bestSolutionCost;
    int neighbourSolutionCost;
    int numberOfCities;
    int iterationsSinceChange;



    // methods
    void generateGreedySolution();


    void printSolution(vector<int>solutionPath);

    int calculateSolutionCost(vector<int> path);

    void generateNeighbourSwap();
    void generateNeighbour2Opt();


  //  void shuffleSolution();

    void TSSolver( int maxDurationInSeconds, int maxIterations, int neighbourMethod);

    void generateRandomSolution();
};


#endif //TS_TABUSEARCH_H
