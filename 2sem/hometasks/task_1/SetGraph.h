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

  // Positive weights only
  void AddEdge(int from, int to, int weight);

  // Returns -1 if the edge doesn't exist
  int GetEdgeWeight(const int from, const int to) const;

  virtual int VerticesCount() const;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const;

private:
  std::vector< std::unordered_map<int, int> > neighbours;
};