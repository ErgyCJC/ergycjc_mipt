#ifndef __DSU_HEADER__
#define __DSU_HEADER__

#include <vector>

struct DSU {
    std::vector<int> roots;
    std::vector<int> tree_height;

    DSU(int elements_count);

    int GetRoot(int unit, int height = 0);

    void Unite(int first, int second);
};

#endif