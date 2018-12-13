#ifndef __KSTAT_HEADER__
#define __KSTAT_HEADER__

#include <vector>
#include <cstdlib>
#include <ctime>

class KStat
{
public:
	KStat(std::vector<int>& keys);

    int FindKValue(int k_index); // Поиск k-ой статистики

private:
	std::vector<int>& buffer_;
    int first; // Индекс первого элемента рассматриваемой части массива относительно всех элементов
    int last; // Индекс элемента, следующего за последним элементом рассматриваемой части массива

    int Partition(int pivot_index);

    int ChoosePivot(); // Функция выбора индекса опорного элемента
};

#endif