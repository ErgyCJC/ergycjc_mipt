#ifndef __STACK_HEADER__
#define __STACK_HEADER__

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

#endif