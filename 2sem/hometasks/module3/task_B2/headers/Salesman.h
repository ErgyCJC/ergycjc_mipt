#ifndef __SALESMAN_HEADER__
#define __SALESMAN_HEADER__

#include "Graph.h"
#include "MST.h"
#include <fstream>
#include <stack>

//Salesman Problem-2 solver 
class SalesmanSolver {
public:
    SalesmanSolver(Graph graph);

    double FindPathCost();

private:
    Graph base_graph;

    bool try_match(int v, std::vector<bool>& visited, std::vector<int> vertices, std::vector<int>& matching);
};

#endif