// Задача B

// Contest link: https://contest.yandex.ru/contest/12173/problems/B

// Необходимо написать торгового советника для поиска арбитража.
// Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах.

// Первая строка содержит число N – количество возможных валют (определяет размер таблицы котировок). 
// Далее следует построчное представление таблицы. Диагональные элементы (i, i) пропущены (подразумевается, что курс валюты к себе же 1.0). 
// В элементе таблицы (i, j) содержится обменный курс i->j. 
// Если обмен в данном направлении не производится, то -1.

// Выведите YES, если арбитраж есть, и NO, иначе.

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <climits>

//============================//============================//============================//

class DoubleArcGraph {
public:
    DoubleArcGraph(int v_count);

    void AddEdge(int from, int to, double weight);

    virtual int Size() const;

    bool ContainsNegativeCycle();

private:
    struct Edge {
        int from;
        int to;
        double weight;

        Edge(int _from, int _to, double _weight) : from(_from), to(_to), weight(_weight) {}
    };

  std::vector<Edge> edges;
  int v_count;
};

DoubleArcGraph::DoubleArcGraph(int _v_count) : v_count(_v_count) {}

void DoubleArcGraph::AddEdge(int from, int to, double weight) {
    edges.emplace_back(from, to, weight);
}

int DoubleArcGraph::Size() const {
    return v_count;
}

bool DoubleArcGraph::ContainsNegativeCycle() {
    // Bellman-Ford negative cycle searching algorithm; T(|V|, |E|) = O(2*|E|*|V|) = O(|E|*|V|)
    for (int source_v = 0; source_v < v_count - 1; ++source_v) {
        std::vector<long double> distance(v_count, __DBL_MAX__);
        distance[source_v] = 0.0;
        
        for (auto e : edges) {
            if (distance[e.from] != __DBL_MAX__ && distance[e.from] + e.weight < distance[e.to] ) {
                distance[e.to] = distance[e.from] + e.weight;
            }
        }

        for (auto e : edges) {
            if (distance[e.from] != __DBL_MAX__ && distance[e.from] + e.weight < distance[e.to] ) {
                return true;
            }
        }
    }

    return false;
}

//============================//============================//============================//

int main(int argc, char** argv) {
    int dimension;
    double value;

    std::cin >> dimension;
    DoubleArcGraph graph(dimension);

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (i == j) {
                continue;
            }

            std::cin >> value;
            graph.AddEdge(i, j, -std::log10(value));
        }
    }

    std::cout << (graph.ContainsNegativeCycle() ? "YES\n" : "NO\n");
    return 0;
}