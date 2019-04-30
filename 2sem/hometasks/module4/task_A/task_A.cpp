// Задача 1. Вторая статистика (RMQ)
// Contest link: https://contest.yandex.ru/contest/12703/problems/A/

// Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.
// Для решения задачи используйте структуру данных Sparse Table.
// Требуемое время обработки каждого диапазона O(1). Время подготовки структуры данных O(n*logn)

// В первой строке заданы 2 числа: размер последовательности N и количество диапазонов M.
// Следующие N целых чисел задают последовательность. Далее вводятся M пар чисел - границ диапазонов.
// Гарантируется, что каждый диапазон содержит как минимум 2 элемента.

// Для каждого из M диапазонов напечатать элемент последовательности - 2ю порядковую статистику. По одному числу в строке.

#include <vector>
#include <cmath>
#include <climits>
#include <iostream>
#include <utility>

class Stat2Solver {
public:
    Stat2Solver(std::vector<int>& seq) {
        // Построение Sparse Table
        int lines_count = static_cast<int>(std::ceil(std::log2(seq.size())));
        int elements_count = static_cast<int>(seq.size());

        // Элемент SparseTable - std::pair<int, int>
        // e.first - 1-статистика, e.second - 2-статистика
        sparse_table.resize(lines_count, std::vector<std::pair<int, int>>(elements_count));

        // Инициализация первой колонки SparseTable:
        // обе первые статистики для промежутка из 1 элемента - сам элемент
        for (int elem_index = 0; elem_index < elements_count; ++elem_index) {
            sparse_table[0][elem_index]. = std::make_pair(seq[elem_index], seq[elem_index]);
        }

        // Рекурсивное заполнение SparseTable
        for (int line = 1; line < lines_count; ++line) {
            for (int row = 0; row < elements_count - (1 << line) + 1; ++row) {
                sparse_table[line][row] = GetPairsStats(sparse_table[line - 1][row], sparse_table[line - 1][row + (1 << (line - 1))]);
            }
        }
    }

    // Метод для получения 2-статистики из построенной ранее SparseTable
    int GetSecondStat(int left, int right) {
        // Range Upper Bound
        int rub = static_cast<int>(std::ceil(std::log2(right - left + 1))) - 1;

        return GetPairsStats(sparse_table[rub][left], sparse_table[rub][right - (1 << rub) + 1]).second;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> sparse_table;

    std::pair<int, int> GetPairsStats(std::pair<int, int> pair1, std::pair<int, int> pair2) {
        // Выбор из 4 значений две первые статистики (это должны быть разные числа)
        // И формаирование из них пары по возрастанию
        
        std::vector<int> values{pair1.first, pair1.second, pair2.first, pair2.second};
        int stat1 = INT_MAX, stat2 = INT_MAX;

        for (auto value : values) {
            if (value < stat1) {
                stat1 = value;
            }
        }
        for (auto value : values) {
            if (value < stat2 && value != stat1) {
                stat2 = value;
            }
        }

        return std::make_pair(stat1, stat2);
    }
};

int main(int argc, char** argv) {
    int seq_length, requests_count;
    std::cin >> seq_length >> requests_count;

    std::vector<int> sequence(seq_length);
    for (auto& e : sequence) {
        std::cin >> e;
    }

    Stat2Solver solver(sequence);

    for (int i = 0; i < requests_count; ++i) {
        int left, right;
        std::cin >> left >> right;

        std::cout << solver.GetSecondStat(left - 1, right - 1) << "\n";
    }
    return 0;
}