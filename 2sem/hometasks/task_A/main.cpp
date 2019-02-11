#include "ListGraph.h"
#include "ArcGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

int main(int argc, char** argv) {
    ListGraph g1(5);

    g1.AddEdge(0, 1);
    g1.AddEdge(1, 0);
    g1.AddEdge(0, 2);
    g1.AddEdge(2, 0);
    g1.AddEdge(1, 2);
    g1.AddEdge(2, 1);
    g1.AddEdge(3, 0);
    g1.AddEdge(0, 3);
    g1.AddEdge(2, 4);
    g1.AddEdge(4, 2);
    g1.AddEdge(1, 3);
    g1.AddEdge(3, 1);
    g1.AddEdge(3, 4);
    g1.AddEdge(4, 3);

    MatrixGraph g2(&g1);
    SetGraph g3(&g2);
    ArcGraph g4(&g3);
    ListGraph g1_copy(&g1);

    return 0;
}