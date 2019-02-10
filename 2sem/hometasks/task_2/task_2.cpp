#include <vector>
#include <iostream>
#include <stack>
#include <cmath>

// Graph implementation - copy-paste from task 1.1
struct IGraph {

  virtual ~IGraph() {}

  virtual void AddEdge(int from, int to) = 0;

  virtual int VerticesCount() const = 0;

  virtual void GetNextVertices(int vertex,
                               std::vector<int> &vertices) const = 0;
  virtual void GetPrevVertices(int vertex,
                               std::vector<int> &vertices) const = 0;
};

//============================//============================//============================

class ListGraph : public IGraph {
public:
  ListGraph(int vertices_count);

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

ListGraph::ListGraph(int vertices_count) {
  neighbours.resize(vertices_count);
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

//============================//============================//============================

// Returns -1, if there are no 'visible' cycles from the root_vertex cycles, or the length of the shortest one
int search_cycle(const ListGraph& graph, const int root_v) {
    // All marked white
    // 0 - white; 1 - grey; 2 - black
    std::vector<int> colored(graph.VerticesCount(), 0);

    // Contains vertices' parents in dfs-path
    std::vector<int> parents(graph.VerticesCount(), root_v);

    // Contains index of last processed child in children-array for each vertex
    // Is need to have one-line-path on each dfs step, not tree
    std::vector<int> processed(graph.VerticesCount(), 0);

    // Contains producing vertices on each dfs step
    std::stack<int> dfs_path;
    dfs_path.push(root_v);

    bool is_cycle_found = false;
    bool turn_back = true; // Indicates was the last turn forward (into potential cycle) or back

    // DFS
    while (!dfs_path.empty()) {
      int current_v = dfs_path.top();

      if (colored[current_v] == 1 && !turn_back) { // Cycle is found
        is_cycle_found = true;
        break;
      }

      colored[current_v] = 1; // Marked grey

      // There is no need to check if the current vertex is black (lecture lemma)
      colored[current_v] = 1; // Marked current vertex grey

      // Contains children of the current vertex
      std::vector<int> children;
      graph.GetNextVertices(current_v, children);

      // Is the next child of current vertex its parent?
      if (processed[current_v] < children.size() && children[processed[current_v]] == parents[current_v]) {
        // Skip parent of the current vertex
        ++processed[current_v];
      }

      if (processed[current_v] == children.size()) { // All children are processed
        colored[current_v] = 2; // Marked black
        dfs_path.pop();

        turn_back = true; // Going back, not in a cycle
      }
      else { // Go to the next child
        int next_v = children[processed[current_v]];
        ++processed[current_v];

        dfs_path.push(next_v);

        parents[next_v] = current_v; // Set parent info`

        turn_back = false; // Going forward
      }
    }

    if (is_cycle_found) {
      // Going back on the dfs path until the common for cycle vertex is not found
      int length = 0;
      int common_v = dfs_path.top();
      dfs_path.pop();

      while (dfs_path.top() != common_v) {
        ++length;
        dfs_path.pop();
      }

      return length + 1;
    }

    return -1;
}

// Returns -1, if there are no cycles in graph, or the length of the shortest one
int min_cycle_length(const ListGraph& graph) {
    int min_cycle_length = -1;

    for (int i = 0; i < graph.VerticesCount(); ++i) {
      int cycle_length = search_cycle(graph, i);

      if (cycle_length < min_cycle_length || min_cycle_length == -1) {
        min_cycle_length = cycle_length;
      }
    }

    return min_cycle_length;
}

//============================//============================//============================

int main(int argc, char** argv) {
    int vertices_count, edges_count;

    std::cin >> vertices_count >> edges_count;
    ListGraph graph(vertices_count);

    for (int i = 0; i < edges_count; ++i) {
        int from, to;
        std::cin >> from >> to;

        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    std::cout << min_cycle_length(graph);

    return 0;
}