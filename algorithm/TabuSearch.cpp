


#include "TabuSearch.h"


#include <random>
#include <iostream>
#include <algorithm>
#include "TabuSearch.h"
#include "../utils/Timer.h"

TabuSearch::TabuSearch(Graph &graph) : tabuList(graph.vertices * 2), g(graph.vertices) { // grapgh vetrices okey
    g = graph;
    currentSolution = new int[g.vertices];
    neighbourSolution = new int[g.vertices];
    bestSolution = new int[g.vertices];
    currentSolutionCost = 0;
    neighbourSolutionCost = INT_MAX;
    bestSolutionCost = INT_MAX;
    iterationsSinceChange = 0;
    numberOfCities = g.vertices;


}

void TabuSearch::generateGreedySolution() {
    bool *visited = new bool[numberOfCities];
    for(int i = 0; i < numberOfCities; i++){
        visited[i] = false;
    }
    int currentCity = 0;
    currentSolution[0] = currentCity;
    visited[currentCity] = true;

    for(int i = 1; i < numberOfCities; i++) {
        int nearestCity = -1;
        int minDistance = INT_MAX;

        for(int j = 0; j < numberOfCities; j++) {
            if(!visited[j] && g.edges[currentCity][j] < minDistance){
                nearestCity = j;
                minDistance = g.edges[currentCity][j];
            }
        }
        currentSolution[i] = nearestCity;
        visited[nearestCity] = true;
        currentSolutionCost += minDistance;
        currentCity = nearestCity;
    }
    currentSolutionCost += g.edges[currentCity][currentSolution[0]];

    std::copy(currentSolution,currentSolution + numberOfCities,bestSolution);
    bestSolutionCost = currentSolutionCost;
    printSolution(currentSolution);
    std::cout << "best solution cost:" << bestSolutionCost;
    delete[] visited;
}

void TabuSearch::printSolution(int *solutionPath) {
    for(int city = 0; city < numberOfCities; city++){
        std::cout<< solutionPath[city] << "-> ";
    }
    std::cout << solutionPath[0];


}

int TabuSearch::calculateSolutionCost(int *path) {
    int cost = 0;
    for(int i = 0; i < numberOfCities - 1; i++) {
        cost += g.edges[path[i]][path[i+1]];
    }
    cost += g.edges[path[numberOfCities-1]][path[0]];

    return cost;
}
void TabuSearch::generateRandomSolution() {
    // Create an array representing the indices of cities
    int* indices = new int[numberOfCities];
    for (int i = 0; i < numberOfCities; ++i) {
        indices[i] = i;
    }

    // Shuffle the indices array to create a random permutation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(indices, indices + numberOfCities, gen);

    // Assign the shuffled indices to the currentSolution array
    for (int i = 0; i < numberOfCities; ++i) {
        currentSolution[i] = indices[i];
    }

    // Calculate the cost of the random solution
    currentSolutionCost = calculateSolutionCost(currentSolution);

    // Clean up memory
    delete[] indices;
}
void TabuSearch::generateNeighbourSwap() {

    int city1, city2;

    std::copy(currentSolution, currentSolution + numberOfCities, neighbourSolution);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomVertex(0, numberOfCities - 1);
    do {
        city1 = randomVertex(gen);
        city2 = randomVertex(gen);
    }while(city1 == city2 || tabuList.findMove(city1, city2));
    if (city1 > city2) {
        std::swap(city1, city2);
    }
    std::swap(neighbourSolution[city1], neighbourSolution[city2]);
    neighbourSolutionCost = calculateSolutionCost(neighbourSolution);
    tabuList.push(city1,city2);
}




void TabuSearch::TSSolver(int maxDurationInSeconds,int maxIterations, int neighbourMethod) {
    generateGreedySolution();


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double random_number = dis(gen);
    Timer timer;
    timer.start();
    int iteration = 0;

    while(timer.mili() < maxDurationInSeconds * 1000 && iteration < maxIterations) {

        if (iterationsSinceChange >= maxIterations * 0.2) {
            std::cout << "***********************************************************************************************************\n";
            tabuList.clear();

//            // Accept the non-improving neighbor
//            std::copy(neighbourSolution, neighbourSolution + numberOfCities, currentSolution);
//            currentSolutionCost = neighbourSolutionCost;
//            std::cout << "CURRENT COST AFTER ACCEPTING NON-IMPROVING NEIGHBOR:" << currentSolutionCost << "\n";
//            printSolution(currentSolution);
            generateRandomSolution();
            iterationsSinceChange = 0;
        }

        switch(neighbourMethod){
            case 1:
                generateNeighbourSwap();
                break;
            case 2:
                generateNeighbour2Opt();
                break;
            case 3:
                if(random_number < 0.5) {
                    generateNeighbourSwap();
                } else
                    generateNeighbour2Opt();
                break;
            default:
                std::cout << "WRONG PAREAMETERS FOR DEFING NEIGHBOUR SOLUTION\n";
                break;
        }
        timer.stop();
//        std::cout << "\nCzas uplynniety\n";
//        std::cout << timer.mili() * 1000 << " sekund\n";

        if (neighbourSolutionCost < currentSolutionCost) {
            iterationsSinceChange = 0;
            std::copy(neighbourSolution, neighbourSolution + numberOfCities, currentSolution);
            currentSolutionCost = calculateSolutionCost(currentSolution);
            std::cout << "\nbestCurrent cost = " << currentSolutionCost << "\n";
            if (currentSolutionCost < bestSolutionCost) {
                std::copy(currentSolution, currentSolution + numberOfCities, bestSolution);
                bestSolutionCost = calculateSolutionCost(bestSolution);
                printSolution(bestSolution);
                std::cout << "\nbestSolution cost = " << bestSolutionCost << "\n";
            }
        } else {
            iterationsSinceChange++;
        }
        iteration++;

    }
    std::cout << "Final solution: ";
    printSolution(bestSolution);
    std::cout << "\nFinal solution cost: " << bestSolutionCost;
    // Clear dynamically allocated arrays and tabu list
    delete[] currentSolution;
    delete[] neighbourSolution;
    delete[] bestSolution;
    tabuList.clear();

}




void TabuSearch::generateNeighbour2Opt() {
    int city1, city2, city3, city4;

    std::copy(currentSolution, currentSolution + numberOfCities, neighbourSolution);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomVertex(0, numberOfCities - 1);

    do {
        city1 = randomVertex(gen);
        city2 = randomVertex(gen);
        city3 = randomVertex(gen);
        city4 = randomVertex(gen);
    } while (city1 == city2 || city3 == city4 || tabuList.findMove(city1, city2) || tabuList.findMove(city3, city4));

    // Check if the move is already in the tabuList
    if (!tabuList.findMove(city1, city2) && !tabuList.findMove(city3, city4)) {
        std::swap(neighbourSolution[city1], neighbourSolution[city2]);
        std::swap(neighbourSolution[city3], neighbourSolution[city4]);
        neighbourSolutionCost = calculateSolutionCost(neighbourSolution);
        tabuList.push(city1, city2);
        tabuList.push(city3, city4);
    }
}

TabuSearch::~TabuSearch() {
    delete[] currentSolution;
    delete[] neighbourSolution;
    delete[] bestSolution;

}











