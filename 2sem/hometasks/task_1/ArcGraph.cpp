#include "ArcGraph.h"

ArcGraph::ArcGraph(const int verticesCount) : vertices_count(verticesCount) {}

ArcGraph::~ArcGraph() {}

void ArcGraph::AddEdge(int from, int to) {
  edges.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
  return vertices_count;
}

void ArcGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();

    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i].first == vertex) {
            vertices.push_back(edges[i].second);
        }
    }
}

void ArcGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();

    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i].second == vertex) {
            vertices.push_back(edges[i].first);
        }
    }
}