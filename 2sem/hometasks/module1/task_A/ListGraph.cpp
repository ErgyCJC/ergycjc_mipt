#include "ListGraph.h"

//*********************//

  ListGraph::ListGraph(const ListGraph& graph) {
    this->neighbours = graph.neighbours;
  }

  ListGraph& ListGraph::operator=(const ListGraph& graph) {
    this->neighbours = graph.neighbours;
    return *this;
  }

  //*********************//

ListGraph::ListGraph(int verticesCount) {
  neighbours.resize(verticesCount);
}

ListGraph::ListGraph(const IGraph* source_graph) : ListGraph(source_graph->VerticesCount()) {
  std::vector<int> children;

    for (int i = 0; i < VerticesCount(); ++i) {
        source_graph->GetNextVertices(i, children);
        for (size_t v = 0; v < children.size(); ++v ) {
            AddEdge(i, children[v]);
        }
    }
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

void ListGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
  vertices.clear();

  for (size_t v = 0; v < neighbours.size(); ++v) {
    for (size_t i = 0; i < neighbours[v].size(); ++i) {
      if (neighbours[v][i] == vertex) {
        vertices.push_back(v);
      }
    }
  }
}

ListGraph& ListGraph::operator=(const IGraph& graph) {
    neighbours.assign(graph.VerticesCount(), std::vector<int>());
    for (int i = 0; i < VerticesCount(); ++i) {
        std::vector<int> children;
        graph.GetNextVertices(i, children);

        for (auto v : children) {
            AddEdge(i, v);
        }
    }

    return *this;
}