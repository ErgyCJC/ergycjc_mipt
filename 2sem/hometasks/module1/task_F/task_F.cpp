// Task F

// Contest Link: https://contest.yandex.ru/contest/11884/problems/F/

// Дан ориентированный граф.
// Определите, какое минимальное число ребер необходимо добавить,
// чтобы граф стал сильносвязным. В графе возможны петли.

// В первой строке указывается число вершин графа V, во второй – число ребер E,
// в последующих – E пар вершин, задающих ребра.

// Вывести минимальное число ребер k.

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

//===========================//===========================//===========================//

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



//===========================//===========================//===========================//

class Compresser {
public:
  Compresser(IGraph& _graph) : graph(_graph), v_count(graph.VerticesCount()) {}

  ~Compresser() = default;

  // Counting edges to make graph strongly connected
  int SCAdding() {
    properties.assign(v_count, VertexProperties());
    global_index = 0;

    sc_components.assign(v_count, -1);
    scc_count = 0;
    
    for (int v = 0; v < v_count; ++v) {
      if (properties[v].index == -1) {
        StrongConnect(v);
      }
    }

    // Is SCC flow-in or flow-out
    std::vector<bool> is_flow_in(scc_count, true);
    std::vector<bool> is_flow_out(scc_count, true);

    for (int i = 0; i < v_count; ++i) {
      std::vector<int> children;
      graph.GetNextVertices(i, children);

      for (auto v : children) {
        if (sc_components[i] != sc_components[v]) {
          is_flow_in[sc_components[i]] = false;
          is_flow_out[sc_components[v]] = false;
        }
      }
    }

    int in_count = 0, out_count = 0;

    for (int component = 0; component < scc_count; ++component) {
      in_count += static_cast<int>(is_flow_in[component]);
      out_count += static_cast<int>(is_flow_out[component]);
    }

    return scc_count == 1 ? 0 : std::max(in_count, out_count);
  }

  // DFS-function (name is taken from an article about the algorithm)
  void StrongConnect(int v) {
    properties[v].index = properties[v].lowlink = ++global_index;
    dfs_path.push(v);
    properties[v].on_stack = true;

    std::vector<int> children;
    graph.GetNextVertices(v, children);
    for (auto child : children) {
      if (properties[child].index == -1) {
        StrongConnect(child);
        properties[v].lowlink = std::min(properties[v].lowlink, properties[child].lowlink);
      }
      else if (properties[child].on_stack) {
        properties[v].lowlink = std::min(properties[v].lowlink, properties[child].index);
      }
    }

    int tmp_v;
    if (properties[v].lowlink == properties[v].index) {
      while (dfs_path.top() != v) {
        tmp_v = dfs_path.top();
        sc_components[tmp_v] = scc_count;
        
        properties[tmp_v].on_stack = false;
        dfs_path.pop();
      }
      
      // Last vertex in SCC
      tmp_v = dfs_path.top();
      sc_components[tmp_v] = scc_count;
      properties[tmp_v].on_stack = false;
      dfs_path.pop();

      ++scc_count;
    }
  }

private:
  struct VertexProperties {
    bool on_stack;
    int index;
    int lowlink;

    VertexProperties() : on_stack(false), index(-1), lowlink(-1) {}
  };

  IGraph& graph;
  int v_count; // Vertices count
  int scc_count;
  int global_index;
  
  // Contains strongly connected components belonging for each vertex
  std::vector<int> sc_components;

  std::vector<VertexProperties> properties;
  std::stack<int> dfs_path;
};

//===========================//===========================//===========================//

int main(int argc, char** argv1) {
    int vertices_count, edges_count, from_v, to_v;
    
    std::cin >> vertices_count >> edges_count;
    ListGraph graph(vertices_count);
    
    for (int i = 0; i < edges_count; ++i) {
        std::cin >> from_v >> to_v;
        graph.AddEdge(from_v - 1, to_v - 1);
    }

    Compresser compresser(graph);
    std::cout << compresser.SCAdding() << "\n";

    return 0;
}