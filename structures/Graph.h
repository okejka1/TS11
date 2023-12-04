//
// Created by mhajd on 03.12.2023.
//

#ifndef PEA_GRAPH_H
#define PEA_GRAPH_H


#include <string>

class Graph {
private:
public:

    int **edges; //  matrix
    int vertices;
    explicit Graph(int v);
    void readGraphDirected(const std::string& s);
    void changeSize(int size);


    virtual ~Graph();

};



#endif //PEA_GRAPH_H
