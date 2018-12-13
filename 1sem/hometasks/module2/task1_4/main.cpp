// Задача 1.4
// Contest link: https://contest.yandex.ru/contest/9378/problems/1_4/
//
// Напишите программу, печатающую набор строк в лексикографическом порядке.
// Строки разделяются символом перевода строки ’ ∖ n ’. Если последний символ в потоке ввода ’ ∖ n ’,
// считать, что после него нет пустой строки. Известно, что либо n < 100, либо n ≤ 1000,
// но при этом число инверсий в данном наборе строк меньше 100. Максимальная длина строки 255 символов.
// Написать свою функцию сравнения строк.

#include <vector>
#include <string>
#include <iostream>
#include "stringInsertSort.h"

int main(int argc, char** argv)
{
    int lines_count;
    std::cin >> lines_count;

    std::vector<std::string> lines_vector;
    for( int i = 0; i < lines_count; ++i ){
        std::string input_line;
        std::cin >> input_line;
        lines_vector.push_back(input_line);
    }

    StringInsertionSort().Sort(lines_vector);

    for( auto it = lines_vector.begin(); it != lines_vector.end(); ++it ){
        std::cout << *it << std::endl;
    }

    return 0;
}