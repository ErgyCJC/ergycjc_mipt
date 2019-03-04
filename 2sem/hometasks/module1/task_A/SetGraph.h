#pragma once

#include <vector>
#include "IGraph.h"
#include "IntHashTable.h"

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

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;

private:
  std::vector<IntHashTable> neighbours;
};