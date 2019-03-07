#include <iostream>
#include <vector>
#include <utility>

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
    // Bellman-Ford negative cycle searching algorithm    
    for (int source_v = 0; source_v < v_count; source_v++) {
        std::vector<double> distance(v_count, -1.0);
        distance[source_v] = 1.0;
        
        for (auto e : edges) {
            if (distance[e.from] != -1.0 && distance[e.to] < distance[e.from] * e.weight) {
                distance[e.to] = distance[e.from] * e.weight;
            }
        }

        for (auto e : edges) {
            if (distance[e.from] != -1.0 && distance[e.to] < distance[e.from] * e.weight)
                return true;
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
            graph.AddEdge(i, j, value);
        }
    }

    std::cout << (graph.ContainsNegativeCycle() ? "YES\n" : "NO\n");
    return 0;
}