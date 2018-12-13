#include "stack.h"

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

	if( elements_count * 2 == buffer_size ){
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