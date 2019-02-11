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

bool isBigraphPart(const ListGraph& graph, std::vector<bool>& visited, const int root_v) {
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
            if (visited[v] && colors[v] == colors[current_v]) {
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

bool isBigraph(const ListGraph& graph) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    bool is_bigraph_flag = true;

    // Bigraph-check for each connectivity component of the graph
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            visited[i] = true;
            is_bigraph_flag = isBigraphPart(graph, visited, i);
        }
    }

    return is_bigraph_flag;
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

    std::cout << (isBigraph(graph) ? "YES" : "NO") << "\n";
    return 0;
}