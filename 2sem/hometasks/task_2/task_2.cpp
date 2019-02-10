#include <vector>
#include <iostream>
#include <queue>
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
int bfs_cycle_search(const ListGraph& graph, const int root_v) {
    std::vector<int> parent(graph.VerticesCount());
    std::vector<int> depth(graph.VerticesCount(), 0);
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    visited[root_v] = true;

    std::queue<int> bfs_queue;
    bfs_queue.push(root_v);

    int result = -1;

    while (!bfs_queue.empty()) {
        int current_v = bfs_queue.front();
        bfs_queue.pop();
        
        std::vector<int> children;
        graph.GetNextVertices(current_v, children);

        for (auto v : children) {
            if (!visited[v]) {
                bfs_queue.push(v);
                
                parent[v] = current_v;
                visited[v] = true;
                depth[v] = depth[current_v] + 1;
            }
            else if (v != parent[current_v]) {
                result = depth[current_v] + depth[v] + 1;
                break;
            }
        }
    }

    return result;
}

// Returns -1, if there are no cycles in graph, or the length of the shortest one
int min_cycle_length(const ListGraph& graph) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    int min_cycle_length = -1;

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        int cycle_length = bfs_cycle_search(graph, i);
        if (min_cycle_length == -1 || cycle_length < min_cycle_length) {
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