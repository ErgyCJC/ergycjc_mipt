#pragma once

#include "igraph.h"
#include <vector>

class MatrixGraph : public IGraph {
public:
  MatrixGraph(int verticesCount);
  
  virtual ~MatrixGraph();

  virtual void AddEdge(int from, int to);

  virtual int VerticesCount() const;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const;

private:
  std::vector< std::vector<bool> > matrix;
};