// Задача C в ведомости (в контесте - B)
// Contest link: https://contest.yandex.ru/contest/12476/problems/B/
//
// Задан неориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью.
// Найдите максимальный поток из вершины с номером  1 в вершину с номером n.
// 
// Первая строка входного файла содержит n и m — количество вершин и количество ребер графа (2 <= N <= 100, 1 <= m <= 1000).
// Следующие m строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность.
// Пропускные способности не превосходят 10^5.

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <climits>

typedef long long ll;

struct Edge {
    int to; // Вершина-конец ребра
    int back_edge_index; // Индекс reverse-ребра, у которого to - начало, в векторе edges[to]

    ll flow; // Текущий пропущенный через ребро поток
    ll capacity; // Пропускная способность ребра

    Edge(int _to, ll _capacity) : to(_to), capacity(_capacity), flow(0) {}

    // Неиспользованная пропускная способность ребра
    ll Capacity() const {
        return capacity - flow;
    }
};

class Graph {
public:
    Graph(int v_count) : vertices_count(v_count) {
        level.resize(v_count);
        ptr.resize(v_count);
        edges.resize(v_count);
    }

    void InsertEdge(int from_v, int to_v, int weight) {
        edges[from_v].emplace_back(to_v, weight);
        edges[to_v].emplace_back(from_v, 0);

        edges[from_v].back().back_edge_index = edges[to_v].size() - 1;
        edges[to_v].back().back_edge_index = edges[from_v].size() - 1;
    }

    // Метод, запускающий алгоритм Диница и возвращающий значение максимального потока.
    // Этот master-метод нужен для добавления "масштабирования", идея: https://neerc.ifmo.ru/wiki/index.php?title=Алгоритм_масштабирования_потока
    // Без него задача в контест не заходила.
    ll GetMaxFlow(int _start_v, int _end_v) {
        start_v = _start_v;
        end_v = _end_v;

        int max_flow = 0;
        int flow_limit = INT_MAX;

        while (flow_limit > 0) {
            max_flow += DinicAlgorithm(flow_limit);
            flow_limit /= 2;
        }

        return max_flow;
    }

private:
    int vertices_count;
    std::vector<std::vector<Edge>> edges;
    std::vector<int> level; // Уровень вершины в слоистой сети
    std::vector<int> ptr; // Индекс первого неудалённого ребра из соответствующей вершины

    // Вершины 'начало' и 'конец' для пропуска потока
    int start_v;
    int end_v;

    ll DinicAlgorithm(int flow_limit) {
        ll max_flow = 0;
        
        while (BFS(flow_limit)) {
            ptr.assign(vertices_count, 0);

            ll flow = DFS(start_v, LLONG_MAX);
            while (flow != 0) {
                max_flow += flow;
                flow = DFS(start_v, LLONG_MAX);
            }
        }

        return max_flow;
    }

    bool BFS(ll limit) {
        level.assign(vertices_count, -1);
        level[start_v] = 0;

        std::queue<int> bfs_queue;
        bfs_queue.push(start_v);

        while (!bfs_queue.empty()) {
            int from_v = bfs_queue.front();
            bfs_queue.pop();

            for (Edge& e : edges[from_v]) {
                // Обработка новой подходящей вершины
                if (level[e.to] == -1 && e.Capacity() >= limit) {
                    level[e.to] = level[from_v] + 1;
                    bfs_queue.push(e.to);
                }
            }
        }

        // Был ли достигнут сток?
        return level[end_v] != -1;
    }

    ll DFS(int from_v, ll min_flow) {
        if (from_v == end_v || min_flow == 0){
            return min_flow;
        }

        for (int edge_index = ptr[from_v]; edge_index < edges[from_v].size(); ++edge_index) {
            Edge& curr_edge = edges[from_v][edge_index];

            if (level[curr_edge.to] != level[from_v] + 1) {
                continue;
            }

            int delta_flow = DFS(curr_edge.to, std::min(curr_edge.Capacity(), min_flow));
            if (delta_flow != 0) {
                // Процесс насыщения ребра
                curr_edge.flow += delta_flow;
                edges[curr_edge.to][curr_edge.back_edge_index].flow -= delta_flow;

                return delta_flow;
            }

            ++ptr[from_v];
        }

        return 0;
    }
};

int main(int argc, char** argv) {
    int v_count, e_count, from_v, to_v, weight;
    std::cin >> v_count >> e_count;

    Graph graph(v_count);
    for (int i = 0; i < e_count; ++i) {
        std::cin >> from_v >> to_v >> weight;
        graph.InsertEdge(from_v - 1, to_v - 1, weight);
    }

    std::cout << graph.GetMaxFlow(0, v_count - 1);
    return 0;
}