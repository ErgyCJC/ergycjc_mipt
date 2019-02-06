#pragma once

#include "IGraph.h"
#include <vector>
#include <unordered_map>

class SetGraph : public IGraph {
public:
  SetGraph(int verticesCount);

  SetGraph(const IGraph* source_graph);
  
  virtual ~SetGraph();

  virtual void AddEdge(int from, int to);

  virtual int VerticesCount() const;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const;

private:
  std::vector< std::unordered_map<int, bool> > neighbours;
};