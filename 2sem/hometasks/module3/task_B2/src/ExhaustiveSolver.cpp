#include "../headers/ExhaustiveSolver.h"

ExhaustiveSolver::ExhaustiveSolver(Graph graph) : base_graph(graph) {}

double ExhaustiveSolver::FindPathCost() {
    std::vector<bool> visited(base_graph.VCount(), false);
    double min_cost = DBL_MAX;

    for (int i = 0; i < base_graph.VCount(); ++i) {
        visited[i] = true;

        for (int j = 0; j < base_graph.VCount(); ++j) {
            visited[j] = true;
            min_cost = std::min(min_cost, GetMinBranchCost(visited, base_graph.GetWeightBetweenVertices(i, j), j));
            visited[j] = false;
        }

        visited[i] = false;
    }

    return min_cost;
}

double ExhaustiveSolver::GetMinBranchCost(std::vector<bool>& visited, double prev_cost, int from_v) {
    double min_adding_cost = DBL_MAX;

    bool all_vertices_visited = true;

    for (int i = 0; i < base_graph.VCount(); ++i) {
        if (!visited[i]) {
            all_vertices_visited = false;
            visited[i] = true;
            min_adding_cost = std::min(min_adding_cost, GetMinBranchCost(visited, base_graph.GetWeightBetweenVertices(from_v, i), i));
            visited[i] = false;
        }
    }

    if (all_vertices_visited) {
        min_adding_cost = 0.0;
    }

    return prev_cost + min_adding_cost;
}