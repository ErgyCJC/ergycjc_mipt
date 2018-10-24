// Задача 2.3
// Contest link: https://contest.yandex.ru/contest/9378/problems/2_3/
//
// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
// N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
//
// В первой строке записано количество отрезков.
// В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.
//
// Выведите целое число — длину окрашенной части.

#include <iostream>
#include <cstdlib>
#include <vector>
#include "cSection.h"
#include "cHeapSort.h"

int PaintedLengthCalculating(std::vector<CSection>& sections); // Функция подсчёта длины 'объединения' отрезков

int main(int argc, char** argv)
{
    int sections_count;
    std::cin >> sections_count;

    // Ввод вектора отрезков
    std::vector<CSection> sections;
    for( int i = 0; i < sections_count; ++i  ){
		int left_border, right_border;
        std::cin >> left_border >> right_border;
        sections.push_back(CSection(left_border, right_border));
    }

    CHeapSort heap_sort_obj(sections); // Сортировка отрезков по увеличению значения левого конца
    heap_sort_obj.Sort();

    std::cout << PaintedLengthCalculating(sections); // Вывод 'закрашенной' части числовой прямой

    return 0;
}

int PaintedLengthCalculating(std::vector<CSection>& sections)
{
    int painted_length = 0;
    int prev_right = -1; // Правый конец предыдущего отрезка

    for( auto it = sections.begin(); it != sections.end(); ++it ){
        if( prev_right == -1 ){ // Первый отрезок всегда полностью входит в объединение
            prev_right = (*it).right_border;
            painted_length += (*it).right_border - (*it).left_border;
        }
        else if ( prev_right >= (*it).left_border && prev_right < (*it).right_border ) // Если текущий отрезок частично перекрывается предыдущим
        {
            painted_length += (*it).right_border - prev_right;
            prev_right = (*it).right_border;
        }
        else if ( prev_right < (*it).left_border ) // Если текущий отрезок не имеет общих точек с предыдущим
        {
            prev_right = (*it).right_border;
            painted_length += (*it).right_border - (*it).left_border;
        }
    }

    return painted_length;
}