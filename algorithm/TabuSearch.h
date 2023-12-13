

#ifndef TS_TABUSEARCH_H
#define TS_TABUSEARCH_H


#include "../structures/Graph.h"
#include "../structures/TabuList.h"

class TabuSearch {

public:
    TabuSearch(Graph &graph);

// fields
    TabuList tabuList;
    Graph g;
    int numOfCities;
    int *currentSolution;
    int *bestSolution;
    int *neighbourSolution;
    int currentSolutionCost;
    int bestSolutionCost;
    int neighbourSolutionCost;
    int numberOfCities;
    int iterationsSinceChange;



    // methods
    void generateGreedySolution();


    void printSolution(int *solutionPath);

    int calculateSolutionCost(int *path);

    void generateNeighbourSolution();
    void generateNeighbourSolution2();
    void generateNeighbourSolution3();

    void shuffleSolution();

    void TSSolver(int maxIterations);
};


#endif //TS_TABUSEARCH_H
