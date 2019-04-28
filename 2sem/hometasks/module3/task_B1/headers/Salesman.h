#ifndef __SALESMAN_HEADER__
#define __SALESMAN_HEADER__

#include "Graph.h"
#include "MST.h"
#include <fstream>

//Salesman Problem-2 solver 
class SalesmanSolver {
public:
    SalesmanSolver(Graph graph);

    double FindPathCost();

private:
    Graph base_graph;
};

#endif