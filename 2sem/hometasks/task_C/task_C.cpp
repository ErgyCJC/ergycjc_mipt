// Task C

// Contest link: https://contest.yandex.ru/contest/11884/problems/C

// Дан невзвешенный неориентированный граф.
// В графе может быть несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

#include <iostream>
#include <vector>
#include <queue>

//=====================//=====================//=====================//=====================//

// Copy-paste graph implementation (ListGraph)

struct IGraph {

  virtual ~IGraph() {}

  virtual void AddEdge(int from, int to) = 0;

  virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const = 0;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const = 0;
};


class ListGraph : public IGraph {
public:
  ListGraph(int verticesCount);
  
  ListGraph(const IGraph* source_graph);
  
  virtual ~ListGraph() override;

  virtual void AddEdge(int from, int to) override;

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;

private:
  std::vector< std::vector<int> > neighbours;
};

ListGraph::ListGraph(int verticesCount) {
  neighbours.resize(verticesCount);
}

ListGraph::ListGraph(const IGraph* source_graph) : ListGraph(source_graph->VerticesCount()) {
  std::vector<int> children;

    for (int i = 0; i < VerticesCount(); ++i) {
        source_graph->GetNextVertices(i, children);
        for (size_t v = 0; v < children.size(); ++v ) {
            AddEdge(i, children[v]);
        }
    }
}

ListGraph::~ListGraph() {}

void ListGraph::AddEdge(int from, int to) {
  neighbours[from].push_back(to);
}

int ListGraph::VerticesCount() const {
  return static_cast<int>(neighbours.size());
}

void ListGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  vertices = neighbours[vertex];
}

void ListGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (size_t v = 0; v < neighbours.size(); ++v) {
    for (size_t i = 0; i < neighbours[v].size(); ++i) {
      if (neighbours[v][i] == vertex) {
        vertices.push_back(v);
      }
    }
  }
}

//=====================//=====================//=====================//=====================//

// Counts how many are there diffrenet ways with the same shortest length from 'from_v' to 'to_v'
int differentShortestWays(const int& from_v, const int& to_v, const IGraph& graph) {
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
    graph.GetNextVertices(current_v, children);

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

int main(int argc, char** argv) {
  int vertices_count, edges_count, from, to;

  std::cin >> vertices_count >> edges_count;
  ListGraph graph(vertices_count);

  for (int i = 0; i < edges_count; ++i) {
      std::cin >> from >> to;
      graph.AddEdge(from, to); // Undirected graph
      graph.AddEdge(to, from);
  }

  std::cin >> from >> to;
  std::cout << differentShortestWays(from, to, graph) << "\n";
  return 0;
}