// Задача 4 по ведомости (C в контесте)
// Contest link: https://contest.yandex.ru/contest/12476/problems/C/

// В одном из отделов крупной организации работает n человек. Как практически все сотрудники этой организации, они любят пить чай в перерывах между работой.
// При этом они достаточно дисциплинированы и делают в день ровно один перерыв, во время которого пьют чай.
// Для того, чтобы этот перерыв был максимально приятным, каждый из сотрудников этого отдела обязательно пьет чай одного из своих любимых сортов.
// В разные дни сотрудник может пить чай разных сортов. Для удобства пронумеруем сорта чая числами от 1 до m.
// Недавно сотрудники отдела купили себе большой набор чайных пакетиков, который содержит a_1 пакетиков чая сорта номер 1, a_2 пакетиков чая сорта номер 2, ..., a_m пакетиков чая сорта номер m.
// Теперь они хотят знать, на какое максимальное число дней им может хватить купленного набора так, чтобы в каждый из дней каждому из сотрудников доставался пакетик чая одного из его любимых сортов.
// Каждый сотрудник отдела пьет в день ровно одну чашку чая, которую заваривает из одного пакетика. При этом пакетики чая не завариваются повторно.

// Первая строка содержит два целых числа n и m (1 <= n, m <= 50). Вторая строка содержит m целых чисел a_1, ..., a_m (1 <= a_i ≤ 10^6 для всех i от 1 до m).
// Далее следуют n строк — i-я из этих строк описывает любимые сорта i-го сотрудника отдела и имеет следующий формат:
// сначала следует положительное число k_i — количество любимых сортов чая этого сотрудника, а затем идут k_i различных чисел от 1 до m — номера этих сортов.
// Выведите одно целое число — искомое максимальное количество дней.

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

    int VerticesCount() const {
        return vertices_count;
    }

    // Проверка того, что через рёбра, выходищие из вершины с v_index, пропущен максимальный возможный поток
    bool RepleteFlow(int v_index) {
        for (auto edge : edges[v_index]) {
            if (edge.flow != edge.capacity) {
                return false;
            }
        }

        return true;
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

// weight == days count
// Проверка возможности пропустить поток объёма (days * people)
// graph именно копируется, благо ограничения на кол-во вершин в нём небольшие
bool PossibleMatching(int weight, int v_count, Graph graph) {
    for (int v_index = 1; v_index <= v_count; ++v_index) {
        graph.InsertEdge(0, v_index, weight);
    }

    graph.GetMaxFlow(0, graph.VerticesCount() - 1);
    return graph.RepleteFlow(0);
}

// Поиск максимального кол-ва дней (бинпоиск)
int GetDaysCount(int people_count, Graph& graph) {
    int upper = 1, lower = 1;
    while (PossibleMatching(upper, people_count, graph)) {
        lower = upper;
        upper *= 2;
    }
       
    ++upper;
    
    while (lower < upper) {
        int middle = (lower + upper) / 2;
        if (PossibleMatching(middle, people_count, graph)) {
            lower = middle + 1;
        }
        else {
            upper = middle;
        }
    }
    
    return lower - 1;
}

int main(int argc, char** argv) {
    int people_count, tea_kinds_count;
    int tea_amount, kinds_count, tea_kind;

    std::cin >> people_count >> tea_kinds_count;

    Graph graph(people_count + tea_kinds_count + 2);

    for (int tea_id = 0; tea_id < tea_kinds_count; ++tea_id) {
        std::cin >> tea_amount;
        graph.InsertEdge(people_count + tea_id + 1, people_count + tea_kinds_count + 1, tea_amount);
    }

    for (int person_id = 0; person_id < people_count; ++person_id) {
        std::cin >> kinds_count;

        for (int i = 0; i < kinds_count; ++i) {
            std::cin >> tea_kind;
            graph.InsertEdge(person_id + 1, people_count + tea_kind, INT_MAX);
        }
    }

    std::cout << GetDaysCount(people_count, graph);
    return 0;
}