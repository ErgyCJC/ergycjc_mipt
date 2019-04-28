#include "../headers/DSU.h"

DSU::DSU(int elements_count) {
    roots.resize(elements_count);
    for (int i = 0; i < elements_count; ++i) {
        roots[i] = i;
    }

    tree_height.resize(elements_count, 1);
}

int DSU::GetRoot(int unit, int height) {
    if (tree_height[unit] < height) {
        tree_height[unit] = height;
    }

    return (unit == roots[unit]) ? unit : (roots[unit] = GetRoot(roots[unit], height + 1));
}

void DSU::Unite(int first, int second) {
    int first_root = GetRoot(first);
    int second_root = GetRoot(second);

    if (first_root != second_root) {
        if (tree_height[first_root] > tree_height[second_root]) {
            roots[second_root] = first_root;
        }
        else {
            roots[first_root] = second_root;
        }
    }
}