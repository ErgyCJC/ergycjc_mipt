// Задача 5.1
// Contest link: https://contest.yandex.ru/contest/9378/problems/5_1/
//
// Дан массив строк. Количество строк не больше 100000.
// Отсортировать массив методом поразрядной сортировки MSD по символам.
// Размер алфавита - 256 символов. Последний символ строки = ‘0’.

#include <iostream>
#include <vector>
#include <string>
#include "MSDSort.h"

int main()
{
	std::string input_line;
	std::vector<std::string> lines;

	while( std::cin >> input_line ){ // Ввод, пока есть строки
		lines.push_back(input_line);
	}

	MSDSort(lines, 0, lines.size(), 0);

	for( int i = 0; i < lines.size(); ++i ){
		std::cout << lines[i] << '\n';
	}

	return 0;
}