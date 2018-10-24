#ifndef __CHEAPSORT_HEADER__
#define __CHEAPSORT_HEADER__

#include <vector>
#include "cSection.h"

class CHeapSort
{
public:
    CHeapSort(std::vector<CSection>& keys);

    void Sort();

private:
    std::vector<CSection>& buffer_;

    int heap_size_; // Количество элементов кучи

    void SiftDown(int index);

    void SiftUp(int index);

    void Build();
};

#endif