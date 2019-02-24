#pragma once

#include "IGraph.h"
#include <vector>
#include <unordered_map>

class SetGraph : public IGraph {
public:

  //*********************//

  SetGraph(const SetGraph& graph);

  SetGraph& operator=(const SetGraph& graph);

  //*********************//

  SetGraph(int verticesCount);

  SetGraph(const IGraph* source_graph);
  
  virtual ~SetGraph();

  SetGraph& operator=(const IGraph& graph);

  virtual void AddEdge(int from, int to) override;

  // Positive weights only
  void AddEdge(int from, int to, int weight);

  // Returns -1 if the edge doesn't exist
  int GetEdgeWeight(const int from, const int to) const;

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;

private:
  std::vector< std::unordered_map<int, int> > neighbours;
};