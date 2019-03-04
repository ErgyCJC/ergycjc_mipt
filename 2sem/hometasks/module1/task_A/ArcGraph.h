#pragma once

#include "IGraph.h"
#include <vector>
#include <utility>

class ArcGraph : public IGraph {
public:

  //*****************//

  ArcGraph(const ArcGraph& graph);

  ArcGraph& operator=(const ArcGraph& graph);

  //*****************//

  ArcGraph(const int _vertices_count);

  ArcGraph(const IGraph* source_graph);
  
  virtual ~ArcGraph() override;

  ArcGraph& operator=(const IGraph& graph);

  virtual void AddEdge(int from, int to) override;

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;

private:
  std::vector< std::pair<int, int> > edges;
  int vertices_count;
};