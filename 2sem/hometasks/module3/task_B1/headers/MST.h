#ifndef __MST_HEADER__
#define __MST_HEADER__

#include "Graph.h"
#include <utility>

// Возвращает MST для переданного графа
std::vector<Edge> BuildMST(Graph& graph);

#endif