#include "quickSort.h"

// Инициализация ссылки на данные для сортировки и уставновка seed'а для rand()
QuickSort::QuickSort( std::vector<int>& array_ ):
	array(array_) {}

void QuickSort::Sort( int left, int right )
{
	Stack partitions_stack; // Стек подмассивов для упорядочивания, не используется рекурсия произвольной глубины
	partitions_stack.Push( left, right );

	while( !partitions_stack.IsEmpty() ){
		// Выбор очередного подмассива
		left = partitions_stack.GetTopLeft();
		right = partitions_stack.GetTopRight();
		partitions_stack.Pop();

		if( right - left <= 0 ){
			continue;
		}
		else if( right - left < 16 ){ // На малых подмассивах запускается Insertion Sort
			InsertSort( left, right );
			continue;
		}

		// Выбор pivot'а и перемещение его в начало подмассива
		int pivot_index = ChoosePivotIndex(left, right);
		const int pivot = array[pivot_index];
		std::swap( array[pivot_index], array[left] ); 

		// Разбиение массива на 3 части: меньше, равные и большее пивота элементы
		int less_it = left;
		int greater_it = right;

		for( int check_it = left + 1; check_it <= greater_it; ){
			if( array[check_it] < pivot ){
				std::swap( array[less_it], array[check_it] );
				++less_it;
				++check_it;
			}
			else if( array[check_it] > pivot ){
				std::swap( array[check_it], array[greater_it] );
				--greater_it;
			}
			else{
				++check_it;
			}
		}
		// pivot не перемещается обратно в середину массива, т.к. и так будет "поднят" на следующей итерации до верхнего индекса подмассива

		// Запуск следующих частей QSort
		partitions_stack.Push( left, less_it - 1 );
		partitions_stack.Push( greater_it + 1, right );
	}
}

int QuickSort::ChoosePivotIndex( int left, int right ) // Выбор медианы трёх
{
	int middle = (left + right) / 2;
	
	if( array[left] > array[middle] ){
		if( array[right] > array[left] ){
			return left;
		}

		return array[middle] > array[right] ? middle : right;
	}

	if( array[right] > array[middle] ){
		return middle;
	}

	return array[left] > array[right] ? left : right;
}

void QuickSort::QSort()
{
	Sort( 0, array.size() - 1 );
}

void QuickSort::InsertSort( int left, int right )
{
	for( int i = left + 1; i <= right; ++i ){
		int tmp_value = array[i];
		int put_index = i - 1;

		for( ; put_index >= left && array[put_index] > tmp_value; --put_index ){
			array[put_index + 1] = array[put_index];
		}

		array[put_index + 1] = tmp_value;
	}
}