#include "../headers/Salesman.h"

SalesmanSolver::SalesmanSolver(Graph graph) : base_graph(graph) {}

double SalesmanSolver::FindPathCost() {
    // Постоение MST
    std::vector<Edge> mst = BuildMST(base_graph);
    std::vector<bool> visited_vertices(base_graph.VCount());

    double path_cost = 0.0;
    int last_vertex;

    // Выбор начального ребра в цикле
    if (mst.size() > 0) {
        last_vertex = mst[0].to_vertex;
        path_cost = mst[0].weight;
        visited_vertices[mst[0].to_vertex] = visited_vertices[mst[0].from_vertex] = true;
    }

    // Проход по вершинам из MST
    for (int i = 1; i < mst.size(); ++i) {
        Edge& curr_edge = mst[i];
        if (!visited_vertices[curr_edge.from_vertex]) {
            visited_vertices[curr_edge.from_vertex] = true;
            path_cost += base_graph.GetWeightBetweenVertices(last_vertex, curr_edge.from_vertex);
            last_vertex = curr_edge.from_vertex;
        }

        if (!visited_vertices[curr_edge.to_vertex]) {
            visited_vertices[curr_edge.to_vertex] = true;
            path_cost += base_graph.GetWeightBetweenVertices(last_vertex, curr_edge.to_vertex);
            last_vertex = curr_edge.to_vertex;
        }
    }

    return path_cost;
}