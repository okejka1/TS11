


#include "TabuSearch.h"


#include <random>
#include <iostream>
#include "TabuSearch.h"

TabuSearch::TabuSearch(Graph &graph) : tabuList(graph.vertices), g(graph.vertices) {
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

void TabuSearch::generateNeighbourSolution() {
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

void TabuSearch::shuffleSolution() {
    std::copy(currentSolution, currentSolution + numberOfCities, neighbourSolution);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomVertex(0, numberOfCities - 1);

    // Perform a big jump by shuffling a subset of cities (e.g., shuffle cities between pos1 and pos2)
    int pos1 = randomVertex(gen);
    int pos2 = randomVertex(gen);

    if (pos1 > pos2) {
        std::swap(pos1, pos2);
    }

    int subsetSize = pos2 - pos1 + 1;
    int* tempSubset = new int[subsetSize];

    // Copy the subset of cities to tempSubset
    std::copy(neighbourSolution + pos1, neighbourSolution + pos2 + 1, tempSubset);

    // Shuffle the subset of cities using Fisher-Yates shuffle algorithm
    for (int i = subsetSize - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(tempSubset[i], tempSubset[j]);
    }

    // Copy the shuffled subset back to neighbourSolution
    std::copy(tempSubset, tempSubset + subsetSize, neighbourSolution + pos1);

    neighbourSolutionCost = calculateSolutionCost(neighbourSolution);

    // Clean up memory
    delete[] tempSubset;

}


void TabuSearch::TSSolver(int maxIterations) {
    generateGreedySolution();
    int iteration = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double random_number = dis(gen);
    while(iteration < maxIterations) {

        if (iterationsSinceChange >= maxIterations * 0.2) {
            tabuList.clear();
            shuffleSolution();
        } else if(random_number < 0.5)
            generateNeighbourSolution();
        else
            generateNeighbourSolution2();

        if (neighbourSolutionCost < currentSolutionCost) {
            iterationsSinceChange = 0;
            std::copy(neighbourSolution, neighbourSolution + numberOfCities, currentSolution);
            currentSolutionCost = calculateSolutionCost(currentSolution);

            if (currentSolutionCost < bestSolutionCost) {
                std::copy(currentSolution, currentSolution + numberOfCities, bestSolution);
                bestSolutionCost = calculateSolutionCost(bestSolution);
                printSolution(bestSolution);
                std::cout << "\nbestSolution cost = " << bestSolutionCost << "\n";
            }
        } else {
            iterationsSinceChange++;
            iteration++;
        }

    }
    std::cout << "Final solution: ";
    printSolution(bestSolution);
    std::cout << "\nFinal solution cost: " << bestSolutionCost;

}

void TabuSearch::generateNeighbourSolution2() {
    int city1, city2,city3,city4;

    std::copy(currentSolution, currentSolution + numberOfCities, neighbourSolution);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomVertex(0, numberOfCities - 1);
    do {
        city1 = randomVertex(gen);
        city2 = randomVertex(gen);
        city3 = randomVertex(gen);
        city4 = randomVertex(gen);
    }while(city1 == city2 || city3 == city4 || tabuList.findMove(city1, city2) || tabuList.findMove(city3, city4));

    std::swap(neighbourSolution[city1], neighbourSolution[city2]);
    std::swap(neighbourSolution[city3], neighbourSolution[city4]);
    neighbourSolutionCost = calculateSolutionCost(neighbourSolution);
    tabuList.push(city1,city2);
    tabuList.push(city3,city4);
}

void TabuSearch::generateNeighbourSolution3() {

        std::copy(currentSolution, currentSolution + numOfCities, neighbourSolution);

        int pos1, pos2;
        do {
            pos1 = rand() % (numOfCities - 1) + 1;
            pos2 = rand() % (numOfCities - 1) + 1;
        } while (pos1 == pos2 || abs(pos1 - pos2) < 2 || tabuList.findMove(pos1, pos2));

        tabuList.push(pos1, pos2);


        if (pos1 > pos2) {
            std::swap(pos1, pos2);
        }

        // Apply 2-opt swap
        while (pos1 < pos2) {
            std::swap(neighbourSolution[pos1], neighbourSolution[pos2]);
            pos1++;
            pos2--;
        }

        neighbourSolutionCost = calculateSolutionCost(neighbourSolution);

    }




