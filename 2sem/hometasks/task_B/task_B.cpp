// Task 1.2

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

//=================//=================//=================//=================//

int CycleSearch(int root_v, ListGraph& graph) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    visited[root_v] = true;

    // Contains distances between root_v and other vertices
    std::vector<int> depth(graph.VerticesCount(), 0);
    
    // Contains parents of push'ed into bfs-queue vertices
    std::vector<int> parent(graph.VerticesCount());

    std::queue<int> bfs_queue;
    bfs_queue.push(root_v);

    // BFS
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
            // It's a common cycle vertex if it isn't the parent of the current vertex
            else if(v != parent[current_v]){ 
                return  depth[v] + depth[current_v] + 1;
            }
        }
    }

    return graph.VerticesCount() + 1;
}

// Returns min cycle length or -1 if it doesn't exist
int GetMinCycle(ListGraph& graph) {
    int min_cycle_length = graph.VerticesCount() + 1;

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
        
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    std::cout << GetMinCycle(graph) << "\n";
    return 0;
}