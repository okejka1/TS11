
#include <random>
#include <iostream>
#include "Solution.h"
#include "TabuSearch.h"
#include "../utils/Timer.h"
#include "TabuSearch.h"
TabuList TabuSearch::tabulist(800);  // Define the static member variable

Solution TabuSearch::apply(Graph &graph, int maxDurationInSeconds, int neighbourMethod, int maxIterations) {
    tabulist.clear();
    Solution bestSolution = Solution::generateGreedySolution(graph);
    Solution currentSolution = bestSolution;

    long bestSolutionTime;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double random_number = dis(gen);
    Timer timer;
    timer.start();
    int iteration = 0;
    int iterationsSinceChange = 0;

    while(timer.mili() < maxDurationInSeconds * 1000 && iteration < maxIterations) {
        if (iterationsSinceChange >= maxIterations * 0.2) {
            std::cout << "Generating random solution due to being stuck in local optima\n";
            tabulist.clear();


            currentSolution = Solution::generateRandomSolution(graph);
            iterationsSinceChange = 0;
        }
        Solution neigbourSolution;
        switch(neighbourMethod){
            case 1:
                 neigbourSolution = Solution::generateNeighbourSwap(graph, currentSolution);
                break;
            case 2:
                 neigbourSolution = Solution::generateNeighbourSwap(graph, currentSolution);
                break;
            case 3:
                if(random_number < 0.5) {
                    neigbourSolution = Solution::generateNeighbourSwap(graph, currentSolution);
                } else
                    neigbourSolution = Solution::generateNeighbourSwap(graph, currentSolution);
                break;
            default:
                std::cout << "WRONG PAREAMETERS FOR DEFING NEIGHBOUR SOLUTION\n";
                break;
        }
        timer.stop();
        if(neigbourSolution.cost < currentSolution.cost) {
            currentSolution = neigbourSolution;
            currentSolution.cost = Solution::calculateCost(graph, currentSolution);
            if(currentSolution.cost < bestSolution.cost) {
                iterationsSinceChange = 0;
                bestSolution = currentSolution;
                timer.stop();
                bestSolutionTime = timer.mili();
                bestSolution.cost = Solution::calculateCost(graph,bestSolution);
                Solution::print(bestSolution);
                std::cout << "\nbestSolution cost = " << bestSolution.cost << "\n";
                tabulist.push(bestSolution.move.first, bestSolution.move.second);
            }

        }
        iterationsSinceChange++;


        iteration++;
    }
    std::cout << "Final solution: ";
    Solution::print(bestSolution);
    std::cout << "\nFinal solution cost: " << bestSolution.cost << "\n";
    std::cout << "Final solution found in " << bestSolutionTime / 1000 << " seconds\n";
    return bestSolution;
}
