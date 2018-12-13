#ifndef __MERGESORT_HEADER__
#define __MERGESORT_HEADER__

#include <vector>

void Merge(std::vector<int>& buffer, int left, int middle, int right); // Слияние двух упорядоченных частей одного массива

void MergeSort(std::vector<int>& buffer, int left, int right); // Рекурсивная сортировка слиянием

void MergeInOne(std::vector<int>& buffer1, std::vector<int>& buffer2); // Слияние двух упорядоченных массивов в первый из них (оставшаяся часть отсекается)

#endif