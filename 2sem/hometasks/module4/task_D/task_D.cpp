// Задача 3
// Contest link: https://contest.yandex.ru/contest/12703/problems/D/

// Задано дерево с корнем, содержащее (1 <= n <= 100 000) вершин, пронумерованных от 0 до n-1.
// Требуется ответить на m (1 <= m <= 10 000 000) запросов о наименьшем общем предке для пары вершин.
// Запросы генерируются следующим образом. Заданы числа a1, a2 и числа x, y и z.
// Числа a3, ..., a2m генерируются следующим образом: ai = (x * ai-2 + y * ai-1 + z) mod n.
// Первый запрос имеет вид (a1, a2). Если ответ на i-1-й запрос равен v, то i-й запрос имеет вид ((a2i-1 + v) mod n, a2i).
// Для решения задачи можно использовать метод двоичного подъёма.

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <cstdlib>

// dp - предпосчитанная матрица предков

class LCASearcher {
public:
    LCASearcher(int v_count) : vertices_count(v_count) {
        in_times.resize(vertices_count);
        out_times.resize(vertices_count);
        connections.resize(vertices_count);

        log_count = std::ceil(std::log2(vertices_count));
        dp.resize(vertices_count, std::vector<int>(log_count + 1));
    }

    void SetAncestor(int vertex, int ancestor) {
        connections[ancestor].push_back(vertex);
    }

    void Preprocess(int v = 0, int v_parent = 0) {
        global_timer = 0;
        DFS(0, 0);
    }

    int GetLCA(int u, int v) {
        if (IsAncestor(u, v)) {
            return u;
        }
        if (IsAncestor(v, u)) {
            return v;
        }

        for (int i = log_count; i >= 0; --i) {
            if (!IsAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }

        return dp[u][0];
    }

private:
    int vertices_count;
    int log_count;

    // Таймер времени входа/выхода для вершин в процессе DFS
    int global_timer;

    std::vector<int> in_times;
    std::vector<int> out_times;

    // Начальная структура дерева
    std::vector<std::vector<int>> connections;
    
    // Расчитываемая в preprocess матрица предков
    std::vector<std::vector<int>> dp;

    void DFS(int v, int parent) {
        in_times[v] = global_timer++;

        dp[v][0] = parent;
        for (int i = 1; i <= log_count; ++i) {
            dp[v][i] = dp[dp[v][i-1]][i-1];
        }

        for (int next : connections[v]) {
            if (next != parent) {
                DFS(next, v);
            }
        }

        out_times[v] = global_timer++;
    }

    bool IsAncestor(int u, int v) {
        return in_times[u] <= in_times[v] && out_times[u] >= out_times[v];
    }
};

int main(int argc, char** argv) {
    int vertices_count, requests_count;
    std::cin >> vertices_count >> requests_count;

    LCASearcher lca_handler(vertices_count);

    // Считывание струтуры дерева
    for (int i = 1; i < vertices_count; ++i) {
        int ancestor;
        std::cin >> ancestor;
        lca_handler.SetAncestor(i, ancestor);
    }

    lca_handler.Preprocess();

    unsigned long long x, y, z, a1, a2;
    unsigned long long result_sum = 0;
    int last_query_result = 0;

    std::cin >> a1 >> a2;
    std::cin >> x >> y >> z;

    for (int i = 0; i < requests_count; ++i) {        
        last_query_result = lca_handler.GetLCA((a1 + last_query_result) % vertices_count, a2);
        result_sum += static_cast<unsigned long long>(last_query_result);

        // Обноваление параметров запроса
        a1 = (a1 * x + a2 * y + z) % vertices_count;
        a2 = (a2 * x + a1 * y + z) % vertices_count;
    }

    std::cout << result_sum;
    return 0;
}