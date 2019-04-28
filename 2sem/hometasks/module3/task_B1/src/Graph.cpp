#include "../headers/Graph.h"

Edge::Edge(int from_v, int to_v, int _weight) : from_vertex(from_v),
                                                to_vertex(to_v),
                                                weight(_weight) {}

Graph::Graph(int v_count) : vertices_count(v_count), edges_count(0) {
  matrix.resize(vertices_count, std::vector<double>(vertices_count, 0.0));
}

int Graph::VCount() const {
  return vertices_count;
}

int Graph::ECount() const {
  return edges_count;
}

double Graph::GetEdgeWeight(int edge_index) {
  return edges[edge_index].weight;
}

void Graph::InsertEdge(int v_from, int v_to, double weight) {
  ++edges_count;
  edges.emplace_back(v_from, v_to, weight);
  matrix[v_from][v_to] = weight;
}

int Graph::GetEdgeTo(int edge_index) {
  return edges[edge_index].to_vertex;
}
  
int Graph::GetEdgeFrom(int edge_index) {
  return edges[edge_index].from_vertex;
}

double Graph::GetWeightBetweenVertices(int v_index1, int v_index2) {
  return matrix[v_index1][v_index2];
}