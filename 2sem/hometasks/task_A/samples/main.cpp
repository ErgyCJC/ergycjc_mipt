#include <iostream>
#include <queue>

#include "igraph.h"
#include "list-graph.h"

void bfs(IGraph *graph, int vertex, std::vector<int> &distances) {
  distances = std::vector<int>(graph->VerticesCount(), -1);
  std::queue<int> q;
  q.push(vertex);
  distances[vertex] = 0;
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    std::vector<int> neighbors;
    graph->GetNextVertices(current, neighbors);
    for (int i = 0; i < neighbors.size(); ++i) {
      if (distances[neighbors[i]] == -1) {
        q.push(neighbors[i]);
        distances[neighbors[i]] = distances[current] + 1;
      }
    }
  }
}

int getDistance(IGraph *graph, int from, int to) {
  std::vector<int> distances;
  bfs(graph, from, distances);
  return distances[to];
}

int main() {
  IGraph *graph = new ListGraph(6);

  graph->AddEdge(0, 1);
  graph->AddEdge(1, 2);
  graph->AddEdge(2, 3);
  graph->AddEdge(3, 4);
  graph->AddEdge(4, 5);
  graph->AddEdge(5, 0);

  graph->AddEdge(1, 4);

  std::vector<int> nextVertices;
  graph->GetNextVertices(3, nextVertices);

  std::vector<int> prevVertices;
  graph->GetPrevVertices(3, prevVertices);

  std::cout << getDistance(graph, 0, 5) << std::endl;

  delete graph;
  return 0;
}