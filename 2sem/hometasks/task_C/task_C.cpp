// Задача 1_3 (C)

// Contest link: https://contest.yandex.ru/contest/11884/problems/C

// Дан невзвешенный неориентированный граф.
// В графе может быть несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

#include <iostream>
#include <vector>
#include <queue>

//=====================//=====================//=====================//=====================//

// Copy-paste graph implementation
class ListGraph {
public:
    ListGraph(int vertices_count);
  
    virtual ~ListGraph();

    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const;

private:
  std::vector< std::vector<int> > neighbours;
};

//=====================//=====================//=====================//=====================//

// Problem solving function
int differentShortestWays(const int& from_v, const int& to_v, const ListGraph& graph);

//=====================//=====================//=====================//=====================//

int main(int argc, char** argv) {
  int vertices_count, edges_count, from, to;

  std::cin >> vertices_count >> edges_count;
  ListGraph graph(vertices_count);

  for (int i = 0; i < edges_count; ++i) {
      std::cin >> from >> to;
      graph.AddEdge(from, to); // Unoriented
  }

  std::cin >> from >> to;
  std::cout << differentShortestWays(from, to, graph) << "\n";
  return 0;
}

//=====================//=====================//=====================//=====================//

int differentShortestWays(const int& from_v, const int& to_v, const ListGraph& graph) {
  int v_count = graph.VerticesCount(); // Vertices count
  std::vector<int> depth(v_count, 0); // Contains distances between each vertex and 'from_v'
  std::vector<int> ways(v_count, 0); // Contains for each vertex count of optimal ways goinf through it

  ways[from_v] = 1; // 'from_v' is a start vertex

  std::queue<int> bfs_queue;
  bfs_queue.push(from_v);

  // BFS
  while(!bfs_queue.empty()){
    int current_v = bfs_queue.front();
    bfs_queue.pop();

    std::vector<int> children;
    graph.GetNextVertices(current_v, children, false);

    for (auto v : children) {
      // One step difference between an optimal way and 'v' ==> going into the optimal way
      if (depth[v] == depth[current_v] + 1) {
        ways[v] += ways[current_v];
      }
      // Not visited vertex ==> going into possible optimal way
      else if (ways[v] == 0) {
        bfs_queue.push(v);
        depth[v] = depth[current_v] + 1;
        ways[v] = ways[current_v];
      }
    }
  }

  return ways[to_v];
}

//=====================//=====================//=====================//=====================//

ListGraph::ListGraph(int verticesCount) {
  neighbours.resize(verticesCount);
}

ListGraph::~ListGraph() {}

void ListGraph::AddEdge(int from, int to) {
  neighbours[from].push_back(to);
  neighbours[to].push_back(from);
}

int ListGraph::VerticesCount() const {
  return static_cast<int>(neighbours.size());
}

void ListGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  vertices = neighbours[vertex];
}