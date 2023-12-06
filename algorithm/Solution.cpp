
#include "Solution.h"


int Solution::findNearestCity(int currentCity, const Graph &graph, const vector<bool> &visited) {
    int nearestCity = -1;
    int minDistance = INT_MAX;

    for (int i = 0; i < graph.vertices; ++i) {
        if (!visited[i] && graph.edges[currentCity][i] < minDistance) {
            nearestCity = i;
            minDistance = graph.edges[currentCity][i];
        }
    }

    return nearestCity;
}

void Solution::printSolution() {
    std::cout << "Path: ";
    for (int city : path) {
        std::cout << city << " -> ";
    }
    std::cout << path.front();

    std::cout << "\nCost: " << cost << std::endl;
}

int Solution::calculateCost(const Graph &graph) {
    int totalCost = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        totalCost += graph.edges[path[i]][path[i + 1]];
    }
    totalCost += graph.edges[path.back()][path.front()];
    return totalCost;
}

Solution Solution::greedySolution(const Graph &graph) {
    Solution greedySolution;
    int startCity = 0;
    std::vector<bool> visited(graph.vertices, false);
    visited[startCity] = true;
    greedySolution.path.push_back(startCity);
    for (int i = 0; i < graph.vertices - 1; i++) {
        int currentCity =  greedySolution.path.back();
        int nearestCity = greedySolution.findNearestCity(currentCity, graph, visited);
        greedySolution.path.push_back(nearestCity);
        visited[nearestCity] = true;
    }
    greedySolution.cost = greedySolution.calculateCost(graph);

    return greedySolution;
}


