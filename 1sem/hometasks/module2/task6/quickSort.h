#ifndef __QUICKSORT_HEADER__
#define __QUICKSORT_HEADER__

#include <vector>
#include <cstdlib>

#include "stack.h"

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

#endif