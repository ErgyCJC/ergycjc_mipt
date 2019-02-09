#include "SetGraph.h"

SetGraph::SetGraph(int verticesCount) {
  neighbours.resize(verticesCount);
}

SetGraph::SetGraph(const IGraph* source_graph) : SetGraph(source_graph->VerticesCount()) {
    std::vector<int> children;

    for (int i = 0; i < VerticesCount(); ++i) {
        source_graph->GetNextVertices(i, children);
        for (size_t v = 0; v < children.size(); ++v ) {
            AddEdge(i, children[v]);
        }
    }
}

SetGraph::~SetGraph() {}

void SetGraph::AddEdge(int from, int to) {
  neighbours[from].insert({to, 1});
}

void SetGraph::AddEdge(int from, int to, int weight) {
  neighbours[from].insert({to, weight});
}

int SetGraph::GetEdgeWeight(const int from, const int to) const {
  if (neighbours[from].find(to) != neighbours[from].end()) {
    return neighbours[from].at(to);
  }
  else {
    return -1;
  }
  
}

int SetGraph::VerticesCount() const {
  return static_cast<int>(neighbours.size());
}

void SetGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  
  for (size_t i = 0; i < neighbours.size(); ++i) {
      if (neighbours[vertex].find(i) != neighbours[vertex].end()) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}

void SetGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (size_t i = 0; i < neighbours.size(); ++i) {
      if (neighbours[i].find(vertex) != neighbours[i].end()) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}