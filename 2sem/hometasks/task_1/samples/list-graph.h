#pragma once

#include "igraph.h"

class ListGraph : public IGraph {
private:
  std::vector<std::vector<int>> verticesNeighbors;

public:
  ListGraph(int verticesCount);
  virtual ~ListGraph() override;

  virtual void AddEdge(int from, int to) override;

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;
};