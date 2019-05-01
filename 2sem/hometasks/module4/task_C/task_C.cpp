// Задача 2.2
// Contest link: https://contest.yandex.ru/contest/12703/problems/C/

// Дан массив из нулей и единиц a0, a1, ..., an-1. Для каждого запроса [left, right] найдите такой подотрезок al, al+1, ..., ar
// этого массива (0 <= left <= l <= r <= right < n), что числа al, al+1, …, ar являются максимально возможной последовательностью единиц.
// Требуемое время ответа на запрос - O(log n).

#include <iostream>
#include <vector>
#include <cmath>

struct Segment {
    int length;
    int pref_length;
    int suff_length;
    int result;

    Segment(int value = 0) {
        // Конструктор-заглушка для инициализации начальных сегментов
        length = value;
        result = pref_length = suff_length = std::max(0, value);
    }

    Segment(const Segment& left_s, const Segment& right_s) {
        // Слияние двух сегментов в один
        length = left_s.length + right_s.length;
        pref_length = std::max(left_s.pref_length, left_s.length + right_s.pref_length);
        suff_length = std::max(right_s.suff_length, left_s.length + right_s.length);
        result = std::max(left_s.suff_length + right_s.pref_length, std::max(left_s.result, right_s.result));
    }
};

class Solver {
public:
    Solver(std::vector<int>& _seq) : seq(_seq), seq_size(seq.size()) {
        // Построение дерева отрезков
        tree.resize(seq_size * 4);
        BuildTree(1, 0, seq_size - 1);
    }

    int GetOnesSeqLength(int left, int right) {
        // Вызов функции поиска максимальной 
        return Query(1, 0, seq_size - 1, left, right).result;
    }

private:
    std::vector<Segment> tree;
    std::vector<int>& seq;
    int seq_size;

    void BuildTree(int v, int left, int right) {
        if (left == right) {
            // Лист дерева
            tree[v] = Segment(seq[left] == 1 ? 1 : -seq_size);
        }
        else {
            int middle = (left + right) / 2;
            BuildTree(v * 2, left, middle);
            BuildTree(v * 2 + 1, middle + 1, right);
            tree[v] = Segment(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    Segment Query(int v, int tree_left, int tree_right, int left, int right) {
        // Проход по дереву отрезков
        if (left == tree_left && right == tree_right) {
            return tree[v];
        }

        int tree_middle = (tree_left + tree_right) / 2;
        if (right <= tree_middle) {
            return Query(v * 2, tree_left, tree_middle, left, right);
        }
        if (left > tree_middle) {
            return Query(v * 2 + 1, tree_middle + 1, tree_right, left, right);
        }

        return Segment(Query(v * 2, tree_left, tree_middle, left, tree_middle),
                        Query(v * 2 + 1, tree_middle + 1, tree_right, tree_middle + 1, right));
    }
};

int main(int argc, char** argv) {
    int bits_count, requests_count;

    while (std::cin >> bits_count) {
        std::cin >> requests_count;

        std::vector<int> sequence(bits_count);
        for (auto& elem : sequence) {
            std::cin >> elem;
        }

        Solver solver(sequence);

        for (int i = 0; i < requests_count; ++i) {
            int left, right;
            std::cin >> left >> right;
            std::cout << solver.GetOnesSeqLength(left, right) << "\n";
        }
    }

    return 0;
}