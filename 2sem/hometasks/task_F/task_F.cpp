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
    current_index = 0;
    scc_count = 0;
    sc_components.assign(v_count, -1);
    properties.assign(v_count, VertexProperties());

    // Tarjan algorithm for finding strongly connected components in graph
    for (int i = 0; i < v_count; ++i) {
      if (properties[i].index == -1) {
        StrongConnect(i);
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
    
    // return std::max(in_count, out_count);
    return 0;
  }

  // DFS-function (name is taken from an article about the algorithm)
  void StrongConnect(int v) {
    properties[v].index = current_index;
    properties[v].lowlink = current_index;

    ++current_index;

    dfs_path.push(v);
    properties[v].on_stack = true;

    std::vector<int> children;
    graph.GetNextVertices(v, children);

    for (auto i : children) {
      if (properties[i].index == -1) {
        StrongConnect(i);
        properties[i].lowlink = std::min(properties[v].lowlink, properties[i].lowlink);
      }
      else if (properties[i].on_stack) {
        properties[v].lowlink = std::min(properties[v].lowlink, properties[i].index);
      }
    }

    // Saving new SCC
    if (properties[v].index == properties[v].lowlink) {
      int tmp_v;
      
      do {
        tmp_v = dfs_path.top();
        dfs_path.pop();
        properties[tmp_v].on_stack = false;

        sc_components[tmp_v] = scc_count;
      } while(tmp_v != v);
    
      ++scc_count;
    }
  }

private:
  struct VertexProperties {
    bool on_stack;
    int index;
    int parent;
    int lowlink;

    VertexProperties() : on_stack(false), index(-1), parent(-1), lowlink(-1) {}
  };

  IGraph& graph;
  int v_count; // Vertices count
  int current_index;
  int scc_count;
  
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

        // Deleting loops
        if (from_v != to_v) {
            graph.AddEdge(from_v - 1, to_v - 1);
        }
    }

    Compresser compresser(graph);
    std::cout << compresser.SCAdding() << "\n";

    return 0;
}