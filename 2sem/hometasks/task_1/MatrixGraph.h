#pragma once

#include "IGraph.h"
#include <vector>

class MatrixGraph : public IGraph {
public:
  MatrixGraph(int verticesCount);

  MatrixGraph(const IGraph* source_graph);
  
  virtual ~MatrixGraph();

  virtual void AddEdge(int from, int to);
  
  void AddEdge(int from, int to, int weight);

  // Returns -1 of the edge doesn't exist
  int GetEdgeWeight(const int from, const int to) const;

  virtual int VerticesCount() const;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const;

private:
  std::vector< std::vector<int> > matrix;
};