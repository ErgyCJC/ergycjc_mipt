#include "ArcGraph.h"

ArcGraph::ArcGraph(const int _vertices_count) : vertices_count(_vertices_count) {}

ArcGraph::ArcGraph(const IGraph* source_graph) : ArcGraph(source_graph->VerticesCount()) {
    std::vector<int> children;

    for (int i = 0; i < VerticesCount(); ++i) {
        source_graph->GetNextVertices(i, children);
        for (size_t v = 0; v < children.size(); ++v ) {
            AddEdge(i, children[v]);
        }
    }
}

ArcGraph::~ArcGraph() {}

void ArcGraph::AddEdge(int from, int to) {
  edges.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
  return vertices_count;
}

void ArcGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();

    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i].first == vertex) {
            vertices.push_back(edges[i].second);
        }
    }
}

void ArcGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();

    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i].second == vertex) {
            vertices.push_back(edges[i].first);
        }
    }
}

ArcGraph& ArcGraph::operator=(const IGraph& graph) {
    vertices_count = graph.VerticesCount();
    edges.clear();
    
    for (int i = 0; i < vertices_count; ++i) {
        std::vector<int> children;
        graph.GetNextVertices(i, children);

        for (auto v : children) {
            AddEdge(i, v);
        }
    }

    return *this;
}