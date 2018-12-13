// Задача 6
// Contest link: https://contest.yandex.ru/contest/9378/problems/6
//
// Дан массив целых чисел в диапазоне [0..109].
// Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^7 элементов.
// Все значения массива являются элементами псевдо-рандомной последовательности.
// Необходимо отсортировать элементы массива за минимально время и
// вывести каждый десятый элемент отсортированной последовательности.


#include <vector>
#include <iostream>

#include "quickSort.h"

int main(int argc, char** argv)
{
	std::ios::sync_with_stdio(false); // "Ускорение" std::cin

	std::vector<int> array;
	int input_num;

	while( std::cin >> input_num ){
		array.push_back(input_num);
	}

	QuickSort sort_obj( array );
	sort_obj.QSort();

	for( int i = 9; i < array.size(); i += 10 ){
		std::cout << array[i] << " ";
	}
	
	return 0;	
}