#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticesCount) {
  matrix.resize(verticesCount);
  for(size_t i = 0; i < verticesCount; ++i) {
      matrix[i].resize(verticesCount, false);
  }
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::AddEdge(int from, int to) {
  matrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
  return static_cast<int>(matrix.size());
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  
  for (size_t i = 0; i < matrix.size(); ++i) {
      if (matrix[vertex][i]) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}

void MatrixGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (size_t i = 0; i < matrix.size(); ++i) {
      if (matrix[i][vertex]) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}