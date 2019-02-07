#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticesCount) {
  matrix.resize(verticesCount);
  for(size_t i = 0; i < verticesCount; ++i) {
      matrix[i].resize(verticesCount, -1);
  }
}

MatrixGraph::MatrixGraph(const IGraph* source_graph) {
  matrix.resize(source_graph->VerticesCount());
  for(size_t i = 0; i < VerticesCount(); ++i) {
      matrix[i].resize(VerticesCount(), -1);
  }

  std::vector<int> children;
    for (int i = 0; i < VerticesCount(); ++i) {
        source_graph->GetNextVertices(i, children);
        for (size_t v = 0; v < children.size(); ++v ) {
            AddEdge(i, children[v]);
        }
    }
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::AddEdge(int from, int to) {
  matrix[from][to] = 1;
}

void MatrixGraph::AddEdge(int from, int to, int weight) {
  matrix[from][to] = weight;
}

int MatrixGraph::GetEdgeWeight(const int from, const int to) const {
  return matrix[from][to];
}

int MatrixGraph::VerticesCount() const {
  return static_cast<int>(matrix.size());
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  
  for (size_t i = 0; i < matrix.size(); ++i) {
      if (matrix[vertex][i] != -1) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}

void MatrixGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (size_t i = 0; i < matrix.size(); ++i) {
      if (matrix[i][vertex] != -1) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}