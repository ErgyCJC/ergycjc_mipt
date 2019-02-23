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

class MatrixGraph : public IGraph {
public:
  MatrixGraph(int verticesCount);

  MatrixGraph(const IGraph* source_graph);
  
  virtual ~MatrixGraph() override;

  virtual void AddEdge(int from, int to) override;
  
  void AddEdge(int from, int to, int weight);

  // Returns -1 of the edge doesn't exist
  int GetEdgeWeight(const int from, const int to) const;

  virtual int VerticesCount() const override;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const override;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const override;

  bool ExistsEdge(int v1, int v2);

private:
  std::vector< std::vector<int> > matrix;
};

MatrixGraph::MatrixGraph(int verticesCount) {
  matrix.resize(verticesCount);
  for(size_t i = 0; i < verticesCount; ++i) {
      matrix[i].resize(verticesCount, -1);
  }
}

MatrixGraph::MatrixGraph(const IGraph* source_graph) : MatrixGraph(source_graph->VerticesCount()) {
    std::vector<int> children;
    for (int i = 0; i < VerticesCount(); ++i) {
        source_graph->GetNextVertices(i, children);
        for (size_t v = 0; v < children.size(); ++v ) {
            AddEdge(i, children[v]);
        }
    }
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::AddEdge(int from, int to) {
  matrix[from][to] = 1;
}

void MatrixGraph::AddEdge(int from, int to, int weight) {
  matrix[from][to] = weight;
}

int MatrixGraph::GetEdgeWeight(const int from, const int to) const {
  return matrix[from][to];
}

int MatrixGraph::VerticesCount() const {
  return static_cast<int>(matrix.size());
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  
  for (size_t i = 0; i < matrix.size(); ++i) {
      if (matrix[vertex][i] != -1) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}

void MatrixGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (size_t i = 0; i < matrix.size(); ++i) {
      if (matrix[i][vertex] != -1) {
          vertices.push_back(static_cast<int>(i));
      }
  }
}

bool MatrixGraph::ExistsEdge(int v1, int v2) {
    return matrix[v1][v2] != 0;
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
    MatrixGraph graph(vertices_count);
    
    for (int i = 0; i < edges_count; ++i) {
        std::cin >> from_v >> to_v;
        graph.AddEdge(from_v - 1, to_v - 1);
    }

    Compresser compresser(graph);
    std::cout << compresser.SCAdding() << "\n";

    return 0;
}