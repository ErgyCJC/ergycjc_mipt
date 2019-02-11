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

ListGraph::ListGraph(int verticesCount) {
  neighbours.resize(verticesCount);
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

//=====================//=====================//=====================//=====================//

struct Vertex{
        Vertex();

        // Vertex' depth in BFS
        int depth;
        // Number of paths from first vertex
        int paths;
    };

    Vertex::Vertex():
        paths(0),
        depth(0)
{}

int differentShortestWays(const int& from_v, const int& to_v, const ListGraph& graph) {
  std::vector<Vertex> states(graph.VerticesCount());
  states[from_v].paths = 1;

  std::vector<int> depth(graph.VerticesCount(), 0);
  std::vector<int> ways(graph.VerticesCount(), 0);

  ways[from_v] = 1;

  std::queue<int> bfs_queue;
  bfs_queue.push(from_v);

  while(!bfs_queue.empty()){
    int current_v = bfs_queue.front();
    bfs_queue.pop();

    std::vector<int> children;
    graph.GetNextVertices(current_v, children);

    for (auto v : children) {
      if (depth[v] == depth[current_v] + 1) {
        ways[v] += ways[current_v];
      }
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
      graph.AddEdge(from, to);
      graph.AddEdge(to, from);
  }

  std::cin >> from >> to;
  std::cout << differentShortestWays(from, to, graph) << "\n";
  return 0;
}