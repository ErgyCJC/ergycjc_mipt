#include "list-graph.h"

ListGraph::ListGraph(int verticesCount) {
  verticesNeighbors.resize(verticesCount);
}

ListGraph::~ListGraph() {}

void ListGraph::AddEdge(int from, int to) {
  verticesNeighbors[from].push_back(to);
}

int ListGraph::VerticesCount() const {
  return static_cast<int>(verticesNeighbors.size());
}

void ListGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  vertices = verticesNeighbors[vertex];
}

void ListGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  for (size_t v = 0; v < verticesNeighbors.size(); ++v) {
    for (size_t i = 0; i < verticesNeighbors[v].size(); ++i) {
      if (verticesNeighbors[v][i] == vertex) {
        vertices.push_back(v);
      }
    }
  }
}