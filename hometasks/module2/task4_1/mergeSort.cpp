#include "mergeSort.h"

void MergeSort(std::vector<int>& buffer, int left, int right)
{
	if( left + 1 >= right){ // Если в рассматриваемой части массива всего один элемент, то он точно упорядочен
		return;
	}

	int middle = (left + right) / 2; // Разбиение массива по середине
	
	MergeSort(buffer, left, middle); // Сортировка первой половины
	MergeSort(buffer, middle, right); // Сортировка правой половины
	
	Merge(buffer, left, middle, right); // Слияние двух отсортированных половин
}

void Merge(std::vector<int>& buffer, int left, int middle, int right)
{
	int it1 = 0; // Итератор левой части массива
	int it2 = 0; // Итератор правой части массива

	std::vector<int> out; // Вектор-результат работы сортировки

	while( left + it1 < middle && middle + it2 < right ){
		// Если текущий элемент левой половины меньше текущего элемента правой половины
		// И в обеих половинах есть элементы
		if( buffer[left + it1] < buffer[middle + it2] ){
			out.push_back(buffer[left + it1]);
			++it1;
		}
		// Если текущий элемент правой половины меньше текущего элемента левой половины
		// И в обеих половинах есть элементы
		else{
			out.push_back(buffer[middle + it2]);
			++it2;
		}
	}

	// Добавляются оставшиеся элементы первой половины, если вторая закончилась
	while( left + it1 < middle ){
		out.push_back(buffer[left + it1]);
		++it1;
	}

	// Добавляются оставшиеся элементы второй половины, если первая закончилась
	while( middle + it2 < right ){
		out.push_back(buffer[middle + it2]);
		++it2;
	}

	// Копирование упорядоченной последовательности в переданный функции вектор
	for( int i = 0; i < out.size(); ++i ){
		buffer[left + i] = out[i];
	}
}

void MergeInOne(std::vector<int>& buffer1, std::vector<int>& buffer2)
{
	int it1 = 0; // Итератор первой половины
	int it2 = 0; // Итератор второй половины

	std::vector<int> out; // Результирующий вектор

	// Функция аналогична Merge()
	// Только добавляется условие, что суммарное количество уже слитых элементов меньше или равно размеру первого массива
	while( it2 < buffer2.size() && it1 + it2 < buffer1.size() ){
		if( buffer1[it1] < buffer2[it2] ){
			out.push_back(buffer1[it1]);
			++it1;
		}
		else{
			out.push_back(buffer2[it2]);
			++it2;
		}
	}

	while( it1 + it2 < buffer1.size() ){
		out.push_back(buffer1[it1]);
		++it1;
	}

	while( it2 < buffer2.size() && it1 + it2 < buffer1.size() ){
		out.push_back(buffer2[it2]);
		++it2;
	}

	for( int i = 0; i < out.size(); ++i ){
		buffer1[i] = out[i];
	}
}