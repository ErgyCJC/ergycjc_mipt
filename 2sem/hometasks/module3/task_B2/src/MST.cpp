#include "../headers/DSU.h"
#include "../headers/MST.h"

#include <iostream>

std::vector<Edge> BuildMST(Graph& graph) {
    std::vector<Edge> result_edges;
    DSU dsu(graph.VCount());

    for (int e_index = 0; e_index < graph.ECount(); ++e_index) {
        int v_from = graph.GetEdgeFrom(e_index);
        int v_to = graph.GetEdgeTo(e_index);
        double weight = graph.GetEdgeWeight(e_index);

        if (dsu.GetRoot(v_from) != dsu.GetRoot(v_to)) {
            result_edges.emplace_back(v_from, v_to, weight);
            dsu.Unite(v_from, v_to);
        }
    }

    return result_edges;
}