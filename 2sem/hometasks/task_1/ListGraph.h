#pragma once

#include "IGraph.h"
#include <vector>

class ListGraph : public IGraph {
public:
  ListGraph(int verticesCount);
  
  ListGraph(const IGraph* source_graph);
  
  virtual ~ListGraph();

  virtual void AddEdge(int from, int to);

  virtual int VerticesCount() const;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const;

private:
  std::vector< std::vector<int> > neighbours;
};