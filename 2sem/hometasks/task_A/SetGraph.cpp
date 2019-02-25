#include "SetGraph.h"

//*********************//

SetGraph::SetGraph(const SetGraph& graph) {
  neighbours.clear();
  for (auto table : graph.neighbours) {
    neighbours.push_back(table);
  }
}

SetGraph& SetGraph::operator=(const SetGraph& graph) {
  neighbours.clear();
  for (auto table : graph.neighbours) {
    neighbours.push_back(table);
  }
  return *this;
}

//*********************//

SetGraph::SetGraph(int verticesCount) {
  neighbours.assign(verticesCount, IntHashTable());
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
  neighbours[from].Push(to);
}

int SetGraph::VerticesCount() const {
  return static_cast<int>(neighbours.size());
}

void SetGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (int to = 0; to < VerticesCount(); ++to) {
    if (neighbours[vertex].Find(to)) {
      vertices.push_back(to);
    }
  }
}

void SetGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (int from = 0; from < VerticesCount(); ++from) {
    if (neighbours[from].Find(vertex)) {
      vertices.push_back(from);
    }
  }
}

SetGraph& SetGraph::operator=(const IGraph& graph) {
  neighbours.assign(graph.VerticesCount(), IntHashTable());
  std::vector<int> children;

  for (int i = 0; i < VerticesCount(); ++i) {
      graph.GetNextVertices(i, children);
      for (size_t v = 0; v < children.size(); ++v ) {
          AddEdge(i, children[v]);
      }
  }
  return *this;
}