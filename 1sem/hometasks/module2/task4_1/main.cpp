// Задача 4.1
// Contest link: https://contest.yandex.ru/contest/9378/problems/4_1/
// 
// Дана очень длинная последовательность целых чисел длины n.
// Требуется вывести в отсортированном виде её наименьшие k элементов.
// Последовательность может не помещаться в память.
// Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.

#include <iostream>
#include "mergeSort.h"

int main(int argc, char** argv)
{
	long long n; // Общее количество элементов
	int k; // Искомое количество элементов
	std::cin >> n >> k;

	std::vector<int> result; // Вектор, в котором будут хранится минимальные k элементов последовательности

	for( int i = 0; i < k; ++i ){ // Ввод первых k элементов
		int input_num;
		std::cin >> input_num;
		result.push_back(input_num);
	}

	MergeSort(result, 0, result.size()); // Сортировка первых k элементов

	std::vector<int> buffer; // Буфер, который будет хранить следующие k пришедших чисел

	for( long long i = k; i < n; ){ // Ввод оставшейся части чисел, пока не введены все n
		for( int j = 0; j < k && i < n; ++i, ++j){ // Ввод k или меньше (если числе больше нет) чисел в буфер
			int input_num;
			std::cin >> input_num;
			buffer.push_back(input_num);
		}

		MergeSort(buffer, 0, buffer.size()); // Сортировка буфера
		MergeInOne(result, buffer); // Слияние результирующего вектора и буфера

		buffer.clear(); // Очистка буфера перед вводом новых чисел
	}

	for( int i = 0; i < result.size(); ++i ){
		std::cout << result[i] << ' ';
	}

	return 0;
}