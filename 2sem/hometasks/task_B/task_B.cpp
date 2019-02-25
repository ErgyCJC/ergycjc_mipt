// Task B

// Contest link: https://contest.yandex.ru/contest/11884/problems/B

// Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.
// В первой строке вводятся два натуральных числа N и M, не превосходящих 10000.
// Далее идут M строк по 2 числа (от 0 до N-1) - индексы вершин между которыми есть ребро.
// Требуется вывести одно целое число равное длине минимального цикла. Если цикла нет, то вывести -1.

// Почему BFS, а не DFS?
// Потому что DFS потребовал бы хранения дополнительной информации об обработанных потомках для каждоый вершины

#include <vector>
#include <iostream>
#include <queue>

//=================//=================//=================//=================//

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

  //*********************//

  ListGraph(const ListGraph& graph);

  ListGraph& operator=(const ListGraph& graph);

  //*********************//

  ListGraph(int verticesCount);
  
  ListGraph(const IGraph* source_graph);
  
  virtual ~ListGraph() override;

  ListGraph& operator=(const IGraph& graph);

  virtual void AddEdge(int from, int to) override;

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;

private:
  std::vector< std::vector<int> > neighbours;
};

//*********************//

  ListGraph::ListGraph(const ListGraph& graph) {
    this->neighbours = graph.neighbours;
  }

  ListGraph& ListGraph::operator=(const ListGraph& graph) {
    this->neighbours = graph.neighbours;
    return *this;
  }

  //*********************//

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

ListGraph& ListGraph::operator=(const IGraph& graph) {
    neighbours.assign(graph.VerticesCount(), std::vector<int>());
    for (int i = 0; i < VerticesCount(); ++i) {
        std::vector<int> children;
        graph.GetNextVertices(i, children);

        for (auto v : children) {
            AddEdge(i, v);
        }
    }

    return *this;
}

//=================//=================//=================//=================//

// Returns some cycle length in current strongly connected part of graph or |V|+1 if it doesn't exist
int CycleSearch(int root_v, IGraph& graph) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    visited[root_v] = true;

    // Contains distances between root_v and other vertices
    std::vector<int> depth(graph.VerticesCount(), 0);
    
    // Contains parents of push'ed into bfs-queue vertices
    std::vector<int> parent(graph.VerticesCount());

    std::queue<int> bfs_queue;
    bfs_queue.push(root_v);

    while (!bfs_queue.empty()) {
        int current_v = bfs_queue.front();
        bfs_queue.pop();
        
        std::vector<int> children;
        graph.GetNextVertices(current_v, children);

        for (auto v : children) {
            if(!visited[v]){ // Going into a new verex
                bfs_queue.push(v);

                parent[v] = current_v;
                depth[v] = depth[current_v] + 1;
                visited[v] = true;
            }
            // Visited (grey) vertex found;
            // It's a common cycle vertex if it isn't parent of the current vertex
            else if(v != parent[current_v]){ 
                return  depth[v] + depth[current_v] + 1;
            }
        }
    }

    // For being 'ignored' by min-function in GetMinCycle()
    return graph.VerticesCount() + 1;
}

// Returns min cycle length or -1 if it doesn't exist
int GetMinCycle(IGraph& graph) {
  int min_cycle_length = graph.VerticesCount() + 1;

  // This loop will find all cycles and will choose the shortest one if it exists
  for (int i = 0; i < graph.VerticesCount(); ++i) {
    min_cycle_length = std::min(CycleSearch(i, graph), min_cycle_length);
  }

  return (min_cycle_length == graph.VerticesCount() + 1 ? -1 : min_cycle_length);
}

//=================//=================//=================//=================//

int main(int argc, char** argv) {
    int v_count, edges_count, from, to;

    std::cin >> v_count >> edges_count;
    ListGraph graph(v_count);

    for (int i = 0; i < edges_count; ++i) {
        std::cin >> from >> to;
        
        // Undirected graph
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    std::cout << GetMinCycle(graph) << "\n";
    return 0;
}
