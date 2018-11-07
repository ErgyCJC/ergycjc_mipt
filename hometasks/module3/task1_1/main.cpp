// Задача 1.1
// Contest link: https://contest.yandex.ru/contest/9657/problems/1_1/
//
// Дано число N <= 10^4 и последовательность целых чисел из [-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root-->Key <= K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
//
// Выведите элементы в порядке in-order (слева направо).
// Рекурсия запрещена.

#include <iostream>
#include "tree.h"

int main( int argc, char** argv )
{
	Tree<int> tree;

	int count;
	std::cin >> count;
	for( int i = 0; i < count; ++i )
	{
		int input_num;
		std::cin >> input_num;
		tree.Add(input_num);
	}

	tree.PrintInOrder();
	
	return 0;
}