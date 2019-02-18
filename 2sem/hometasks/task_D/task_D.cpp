// Task D

// Contest link: https://contest.yandex.ru/contest/11884/problems/D/

// Дан невзвешенный неориентированный граф. Определить, является ли он двудольным. Требуемая сложность O(V+E).
// Ввод: v:кол-во вершин(макс. 50000), n:кол-во ребер(макс. 200000), n пар реберных вершин.
// Вывод: YES если граф является двудольным, NO - если не является.s

#include <iostream>
#include <vector>
#include <queue>

// ---
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

bool isBigraphPart(const IGraph& graph, std::vector<bool>& visited, const int root_v) {
    std::queue<int> bfs_queue;
    bfs_queue.push(root_v);

    // 0 - unmarked; 1 - first part; 2 - second part
    std::vector<int> colors(graph.VerticesCount(), 0);
    colors[root_v] = 1;

    // BFS
    while (!bfs_queue.empty()) {
        int current_v = bfs_queue.front();
        bfs_queue.pop();

        std::vector<int> children;
        graph.GetNextVertices(current_v, children);

        for (auto v : children) {
            // Two connected vertices from the same part
            if (visited[v] && colors[v] == colors[current_v] && v != current_v) {
                return false;
            }
            
            // Going into a new vertex
            if (!visited[v]) {
                visited[v] = true;
                colors[v] = colors[current_v] == 1 ? 2 : 1;
                bfs_queue.push(v);
            }
        }
    }

    return true;
}

bool isBigraph(const IGraph& graph) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    bool is_bigraph_flag = true;

    // Bigraph-check for each connectivity component of the graph
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            visited[i] = true;
            is_bigraph_flag = isBigraphPart(graph, visited, i);
            if (!is_bigraph_flag) {
              break;
            }
        }
    }

    return is_bigraph_flag;
}

//=====================//=====================//=====================//=====================//

int main(int argc, char** argv) {
    int vertices_count, edges_count, from, to;
    std::cin >> vertices_count >> edges_count;

    if (vertices_count == 0 || edges_count == 0) {
      std::cout << "NO\n";
      return 0;
    }
    
    ListGraph graph(vertices_count);
    for (int i = 0; i < edges_count; ++i) {
        std::cin >> from >> to;
        
        graph.AddEdge(from, to); // Undirected graph
        graph.AddEdge(to, from);
    }

    std::cout << (isBigraph(graph) ? "YES" : "NO") << "\n";
    return 0;
}