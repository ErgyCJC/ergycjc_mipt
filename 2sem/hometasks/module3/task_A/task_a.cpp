// Задача A (Вариант 3. С помощью алгоритма Борувки)
// Contest link: https://contest.yandex.ru/contest/12476/problems/A/
//
// Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.

#include <vector>
#include <iostream>

struct Edge {
    int from;
    int to;
    int weight;

    Edge (int _from, int _to, int _weight) : from(_from), to(_to), weight(_weight) {}
};

// Информация о принадлежности вершины к компоненте
// и ранке дерева
struct Subset {
    int rank;
    int root;

    Subset (int _rank = 0, int _root = -1) : rank(_rank), root(_root) {}
};

class Graph {
public:
    Graph (int v_count) : vertices_count(v_count) {}

    // Мощность V
    int VCount () const {
        return vertices_count;
    }

    // Мощность E
    int ECount () const {
        return edges_count;
    }

    void InsertEdge (int v_from, int v_to, int weight) {
        ++edges_count;
        edges.emplace_back(v_from, v_to, weight);
    }

    // Нахождение веса минимального остовного дерева
    int FindMSTWeight () {
        int MST_weight = 0;

        // Изначально каждая вершина - обособленное дерево
        int trees_count = vertices_count;

        // Информация об компоненте связности каждоый вершины
        std::vector<Subset> subsets(vertices_count);
        
        // Номер минимального инцидентного ребра каждой вершины
        std::vector<int> min_edge;

        for (int i = 0; i < vertices_count; ++i) {
            subsets[i].root = i;
        }

        // Пока все вершины не объединены в единственное дерево - MST
        while (trees_count > 1) {
            min_edge.assign(vertices_count, -1);
            
            // Проход по всем рёбрам
            for (int e = 0; e < edges_count; ++e) {
                // Определение, к какой компоненте связности принадлежат концы ребра e
                int root_from = GetRootVertex(subsets, edges[e].from);
                int root_to = GetRootVertex(subsets, edges[e].to);

                // Если вершины e в разных компонентах связности, то проверка на новое минимальное ребро
                // для обеих вершин
                if (root_from != root_to) {
                    if (min_edge[root_from] == -1 || edges[min_edge[root_from]].weight > edges[e].weight) {
                        min_edge[root_from] = e;
                    }
                    if (min_edge[root_to] == -1 || edges[min_edge[root_to]].weight > edges[e].weight) {
                        min_edge[root_to] = e;
                    }
                }
            }

            // Проход по всем вершинам
            for (int v = 0; v < vertices_count; ++v) {
                if (min_edge[v] != -1) {
                    // Объединение вершин, инцидентых минимальному ребру в 

                    int root_from = GetRootVertex(subsets, edges[min_edge[v]].from);
                    int root_to = GetRootVertex(subsets, edges[min_edge[v]].to);

                    if (root_from != root_to) {
                        MST_weight += edges[min_edge[v]].weight;
                        --trees_count;

                        // Объединение двух деревьев (компонент связности), которым принадлежат root_from и root_to
                        UnionTwoComponents(subsets, root_from, root_to);
                    }
                }
            }
        }

        return MST_weight;
    }

private:

    int vertices_count;
    int edges_count;

    std::vector<Edge> edges;

    // Нахождение 
    int GetRootVertex (std::vector<Subset>& subsets, int index) {
        if (subsets[index].root != index) {
            subsets[index].root = GetRootVertex(subsets, subsets[index].root);
        }

        return subsets[index].root;
    }

    void UnionTwoComponents (std::vector<Subset>& subsets, int tree1, int tree2) {
        int root1 = GetRootVertex(subsets, tree1);
        int root2 = GetRootVertex(subsets, tree2);

        if (subsets[root1].rank < subsets[root2].rank) {
            subsets[root1].root = root2;
        }
        else if (subsets[root2].rank < subsets[root1].rank) {
            subsets[root2].root = root1;
        }
        else {
            subsets[root2].root = root1;
            ++subsets[root1].rank;
        }
    }
};

int main (int argc, char** argv) {
    int v_count, e_count, v_from, v_to, weight;
    std::cin >> v_count >> e_count;

    Graph graph(v_count);
    for (int i = 0; i < e_count; ++i) {
        std::cin >> v_from >> v_to >> weight;
        graph.InsertEdge(v_from - 1, v_to - 1, weight);
    }

    std::cout << graph.FindMSTWeight();
    return 0;
}