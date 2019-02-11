#pragma once

#include "IGraph.h"
#include <vector>

class MatrixGraph : public IGraph {
public:
  MatrixGraph(int verticesCount);

  MatrixGraph(const IGraph* source_graph);
  
  virtual ~MatrixGraph() override;

  virtual void AddEdge(int from, int to) override;
  
  void AddEdge(int from, int to, int weight);

  // Returns -1 of the edge doesn't exist
  int GetEdgeWeight(const int from, const int to) const;

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;

private:
  std::vector< std::vector<int> > matrix;
};