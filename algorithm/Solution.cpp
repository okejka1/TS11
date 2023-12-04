
#include "Solution.h"


int Solution::findNearestCity(int currentCity, Graph &graph, vector<bool>& visited) {
    int nearestCity = -1;
    int minDistance = INT_MAX;

    for(int i = 0; i < graph.vertices; i++) {
        if(!visited[i] && i != currentCity && graph.edges[currentCity][i] < minDistance){
            minDistance = graph.edges[currentCity][i];
            nearestCity = i;
        }
    }
    return nearestCity;
}


