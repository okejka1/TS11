

#ifndef TS_TABUSEARCH_H
#define TS_TABUSEARCH_H


#include <vector>
#include "../structures/Graph.h"
#include "../structures/TabuList.h"
#include "../algorithm/Solution.h"

using namespace std;

class TabuSearch {

public:
    static TabuList tabulist;
    static Solution apply(Graph &graph, int timeInSeconds, int neigbourhoodMethod, int maxIterations);
};


#endif //TS_TABUSEARCH_H
