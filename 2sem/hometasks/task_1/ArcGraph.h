#pragma once

#include "IGraph.h"
#include <vector>
#include <utility>

class ArcGraph : public IGraph {
public:
  ArcGraph(const int verticesCount);
  
  virtual ~ArcGraph();

  virtual void AddEdge(int from, int to);

  virtual int VerticesCount() const;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const;

private:
  std::vector< std::pair<int, int> > edges;
  const int vertices_count;
};