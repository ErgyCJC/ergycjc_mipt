#ifndef __EXHAUSTIVE_SOLVER_HEADER__
#define __EXHAUSTIVE_SOLVER_HEADER__

#include "Graph.h"
#include <vector>
#include <cmath>
#include <float.h>

class ExhaustiveSolver {
public:
    ExhaustiveSolver(Graph graph);

    double FindPathCost();

private:
    Graph base_graph;

    double GetMinBranchCost(std::vector<bool>& visited, double prev_cost, int from_v);
};

#endif