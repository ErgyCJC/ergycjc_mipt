#include "ListGraph.h"
#include "ArcGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

int main(int argc, char** argv) {
    ListGraph g1(5);
    SetGraph g2(&g1);
    MatrixGraph g3(&g2);
    ArcGraph g4(&g3);
    return 0;
}