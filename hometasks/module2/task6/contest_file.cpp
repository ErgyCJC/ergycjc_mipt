// Задача 6
// Contest link: https://contest.yandex.ru/contest/9378/problems/6
//
// Дан массив целых чисел в диапазоне [0..109].
// Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^7 элементов.
// Все значения массива являются элементами псевдо-рандомной последовательности.
// Необходимо отсортировать элементы массива за минимально время и
// вывести каждый десятый элемент отсортированной последовательности.

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <cstring>

class Stack
{
public:
	Stack();

	~Stack();

	void Push( int left_, int right_ );

	void Pop();

	int GetTopLeft();

	int GetTopRight();

	bool IsEmpty();

private:
	// Стек нужен для хранения двух границ подмассивов
	// Поэтому используются дву буффера
	int* buffer_left;
	int* buffer_right;

	int elements_count;
	int buffer_size;
};

struct Pair
{
	int first;
	int second;

	Pair( int first_, int second_, bool bit ): first(first_), second(second_) {}
};

class QuickSort
{
public:
	QuickSort( std::vector<int>& array_ );

	void Sort( int left, int right );

	void QSort();

private:
	std::vector<int>& array;

	int ChoosePivotIndex( int left, int right );

	void InsertSort( int left, int right );
};


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


Stack::Stack():
	elements_count(0), buffer_size(1)
{
	buffer_left = new int[1];
	buffer_right = new int[1];
}

Stack::~Stack()
{
	delete[] buffer_left;
	delete[] buffer_right;
}

void Stack::Push( int left_, int right_ )
{
	if( elements_count == buffer_size ){
		int* tmp_buffer_left = new int[buffer_size * 2];
		int* tmp_buffer_right = new int[buffer_size * 2];

		std::memcpy(tmp_buffer_left, buffer_left, sizeof(int) * buffer_size);
		std::memcpy(tmp_buffer_right, buffer_right, sizeof(int) * buffer_size);

		delete[] buffer_left;
		delete[] buffer_right;

		buffer_left = tmp_buffer_left;
		buffer_right = tmp_buffer_right;

		buffer_size *= 2;
	}

	buffer_left[elements_count] = left_;
	buffer_right[elements_count] = right_;
	++elements_count;
}

void Stack::Pop()
{
	--elements_count;

	if( elements_count * 2 == buffer_size){
		int* tmp_buffer_left = new int[elements_count];
		int* tmp_buffer_right = new int[elements_count];

		std::memcpy(tmp_buffer_left, buffer_left, sizeof(int) * elements_count);
		std::memcpy(tmp_buffer_right, buffer_right, sizeof(int) * elements_count);

		delete[] buffer_left;
		delete[] buffer_right;

		buffer_left = tmp_buffer_left;
		buffer_right = tmp_buffer_right;

		buffer_size = elements_count;
	}
}

int Stack::GetTopLeft()
{
	return buffer_left[elements_count - 1];
}

int Stack::GetTopRight()
{
	return buffer_right[elements_count - 1];
}

bool Stack::IsEmpty()
{
	return elements_count == 0;
}

// Инициализация ссылки на данные для сортировки и уставновка seed'а для rand()
QuickSort::QuickSort( std::vector<int>& array_ ):
	array(array_)
{
	srand( time( nullptr ) );
}

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
		else if( right - left < 64 ){ // На малых подмассивах запускается Insertion Sort
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

int QuickSort::ChoosePivotIndex( int left, int right )
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