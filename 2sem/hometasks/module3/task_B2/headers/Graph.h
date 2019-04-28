#ifndef __GRAPH_HEADER__
#define __GRAPH_HEADER__

#include <vector>

struct Edge {
  int from_vertex;
  int to_vertex;
  double weight;

  Edge(int from_v, int to_v, int _weight);
};

class Graph {
public:
  Graph(int v_count);

  int VCount() const;

  int ECount() const;

  void InsertEdge(int v_from, int v_to, double weight = 1.0);

  double GetEdgeWeight(int edge_index);

  int GetEdgeTo(int edge_index);
  
  int GetEdgeFrom(int edge_index);

  double GetWeightBetweenVertices(int v_index1, int v_index2) const;

  int GetVertexDegree(int v_index) const;

private:
  int vertices_count;
  int edges_count;

  std::vector<Edge> edges;
  std::vector<std::vector<double>> matrix;
  std::vector<int> degrees;
};

#endif