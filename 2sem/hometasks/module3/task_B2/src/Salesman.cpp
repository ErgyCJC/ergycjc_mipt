#include "../headers/Salesman.h"

SalesmanSolver::SalesmanSolver(Graph graph) : base_graph(graph) {}

double SalesmanSolver::FindPathCost() {
    // Построение MST
    std::vector<Edge> mst = BuildMST(base_graph);
    if (mst.empty()) {
        return 0.0;
    }
    
    // Выбор вершин с нечётными степенями
    std::vector<bool> visited(base_graph.VCount(), false);
    std::vector<int> odd_vertices;
    for (auto& edge : mst) {
        if (!visited[edge.from_vertex]) {
            visited[edge.from_vertex] = true;
            if (base_graph.GetVertexDegree(edge.from_vertex) % 2 == 1) {
                odd_vertices.push_back(edge.from_vertex);
            }
        }
        if (!visited[edge.to_vertex]) {
            visited[edge.to_vertex] = true;
            if (base_graph.GetVertexDegree(edge.to_vertex) % 2 == 1) {
                odd_vertices.push_back(edge.to_vertex);
            }
        }
    }

    // Построение минимального паросочетания на выбранных "нечётных" вершинах
    std::vector<int> matching(base_graph.VCount(), -1);
    for (auto v : odd_vertices) {
        visited.assign(base_graph.VCount(), false);
        try_match(v, visited, odd_vertices, matching);
    }

    // Добавление рёбер из паросочетания в построенное MST
    visited.assign(base_graph.VCount(), false);
    for (auto v : odd_vertices) {
        if (!visited[v]) {
            visited[v] = true;
            visited[matching[v]] = true;

            mst.emplace_back(v, matching[v], base_graph.GetWeightBetweenVertices(v, matching[v]));
        }
    }

    // Поиск Эйлерова цикла на отобранном множестве
    std::vector<int> result_seq;
    std::stack<int> st;
    int start_vertex = mst[0].from_vertex;
    st.push(start_vertex);

    while (!st.empty()) {
        int v = st.top();
        bool alone_vertex = true;
        
        for (Edge& edge : mst) {
            if (edge.weight != -1.0 && (edge.to_vertex == v || edge.from_vertex == v)) {
                alone_vertex = false;
                edge.weight = -1.0;

                int another_v = edge.to_vertex;
                if (edge.to_vertex == v) {
                    another_v = edge.from_vertex;
                }

                st.push(another_v);
                break;
            }
        }

        if (alone_vertex) {
            result_seq.push_back(v);
            st.pop();
        }
    }

    // Подсчёт стоимости пути
    double cost = 0.0;
    int from_v = result_seq[0];
    for (int to_index = 1; to_index < result_seq.size(); ++to_index) {
        int to_v = result_seq[to_index];
        cost += base_graph.GetWeightBetweenVertices(from_v, to_v);
        from_v = to_v;
    }

    return cost;
}

bool SalesmanSolver::try_match(int v, std::vector<bool>& visited, std::vector<int> vertices, std::vector<int>& matching) {
    if (visited[v]) {
        return false;
    }
    visited[v] = true;

    for (auto next_v : vertices) {
        if (v == next_v) {
            continue;
        }

        if (matching[next_v] == -1 || try_match(next_v, visited, vertices, matching)) {
            matching[next_v] = v;
            return true;
        }
    }

    return false;
}