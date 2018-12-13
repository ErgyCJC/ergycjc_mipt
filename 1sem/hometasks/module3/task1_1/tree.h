#ifndef __TREE_HEADER__
#define __TREE_HEADER__

#include <iostream>
#include <stack>

template<class T>
class Tree
{
public:
	Tree();

	~Tree();

	void Add( T key );

	void PrintInOrder();

private:
	template<class K>
	struct Node
	{
		K value;

		Node<K>* left;
		Node<K>* right;

		Node(): left(nullptr), right(nullptr) {}
	};

	Node<T>* root;
};

#endif