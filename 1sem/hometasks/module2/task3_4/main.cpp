// Задача 3 'Порядковая статистика'
// Contest link: https://contest.yandex.ru/contest/9378/problems/3/
//
// Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
// Напишите нерекурсивный алгоритм.
// Требования к дополнительной памяти: O(n).
// Требуемое среднее время работы: O(n).
// Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.

#include <vector>
#include <iostream>
#include "kStat.h"

int main(int argc, char** argv)
{
    int keys_count;
    int k_index;
    std::cin >> keys_count >> k_index;

    std::vector<int> keys; // Ввод вектора чисел
    for( int index = 0; index < keys_count; ++index ){
        int input_num;
        std::cin >> input_num;
        keys.push_back(input_num);
    }

    KStat k_stat_searcher(keys); // Объект поиска k-ой порядковой статистики
    int k_value = k_stat_searcher.FindKValue(k_index); // Поиск k-ой порядковой статистики

    std::cout << k_value;

    return 0;
}