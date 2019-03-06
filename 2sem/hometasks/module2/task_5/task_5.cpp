// Задача E

// Contest link: https://contest.yandex.ru/contest/12173/problems/E/

// Полный ориентированный взвешенный граф задан матрицей смежности.
// Постройте матрицу кратчайших путей между его вершинами.
// Гарантируется, что в графе нет циклов отрицательного веса.

// В первой строке вводится единственное число N (1 < N < 100) — количество вершин графа.
// В следующих N строках по N чисел задается матрица смежности графа (j-ое число в i-ой строке — вес ребра из вершины i в вершину j).
// Все числа по модулю не превышают 100. На главной диагонали матрицы — всегда нули.

// Выведите N строк по N чисел — матрицу расстояний между парами вершин, где j-ое число в i-ой строке
// равно весу кратчайшего пути из вершины i в j.

#include <iostream>
#include <vector>
#include <climits>

//========================//========================//========================//

class MatrixGraph {
public:
    MatrixGraph(int v_count);

    void AddEdge(int from, int to, int weight);

    virtual int VerticesCount() const;

    void CalcMinDistancesMatrix(std::vector<std::vector<int>>& distances);

private:
  std::vector< std::vector<int> > matrix;
};

MatrixGraph::MatrixGraph(int v_count) {
    matrix.resize(v_count);
    for(size_t i = 0; i < v_count; ++i) {
        matrix[i].resize(v_count, INT_MAX);
    }
}

void MatrixGraph::AddEdge(int from, int to, int weight) {
    matrix[from][to] = weight;
}

int MatrixGraph::VerticesCount() const {
    return static_cast<int>(matrix.size());
}

void MatrixGraph::CalcMinDistancesMatrix(std::vector<std::vector<int>>& distances) {
    distances = matrix;
    
    for (int i = 0; i < VerticesCount(); ++i) {
        for (int v = 0; v < VerticesCount(); ++v) {
            for (int u = 0; u < VerticesCount(); ++u) {
                if (distances[v][i] + distances[i][u] < distances[v][u]) {
                    distances[v][u] = distances[v][i] + distances[i][u];
                }
            }
        }
    }
}

//========================//========================//========================//

int main(int argc, char** argv) {
    int dimension, weight;
    std::cin >> dimension;

    MatrixGraph graph(dimension);
    for (int v1 = 0; v1 < dimension; ++v1) {
        for (int v2 = 0; v2 < dimension; ++v2) {
            std::cin >> weight;
            graph.AddEdge(v1, v2, weight);
        }
    }

    std::vector<std::vector<int>> distances;
    graph.CalcMinDistancesMatrix(distances);
    for (auto row : distances) {
        for (auto value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
    return 0;
}