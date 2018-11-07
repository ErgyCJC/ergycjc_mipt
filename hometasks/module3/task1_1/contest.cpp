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

#include <stack>
#include <iostream>

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

//=====================//=====================//=====================//=====================//

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

//=====================//=====================//=====================//=====================//

template<class T>
Tree<T>::Tree(): root(nullptr) {}

template<class T>
Tree<T>::~Tree()
{
	std::stack< Node<T>* > nodes;
	
	if( root != nullptr )
	{
		nodes.push( root );
	}

	while( !nodes.empty() )
	{
		Node<T>* tmp_node = nodes.top();
		nodes.pop();

		if( tmp_node->left != nullptr )
		{
			nodes.push( tmp_node->left );
		}

		if( tmp_node->right != nullptr )
		{
			nodes.push( tmp_node->right );
		}

		delete tmp_node;
	}
}

template<class T>
void Tree<T>::Add( T key )
{
	if( root == nullptr )
	{
		root = new Node<T>;
		root->left = root->right = nullptr;
		root->value = key;
		return;
	}

	Node<T>* current_node = root;
	while( true )
	{
		// Создание левого листа
		if( current_node->left == nullptr && key < current_node->value )
		{
			current_node->left = new Node<T>;
			current_node->left->value = key;
			return;
		}
		// Создание правого листа
		else if( current_node->right == nullptr && key >= current_node->value )
		{
			current_node->right = new Node<T>;
			current_node->right->value = key;
			return;
		}
		// Переход в левое поддерево
		else if( current_node->left != nullptr && key < current_node->value )
		{
			current_node = current_node->left;
		}
		// Переход в правое поддерево
		else if( current_node->right != nullptr && key >= current_node->value )
		{
			current_node = current_node->right;
		}
	}
}

template<class T>
void Tree<T>::PrintInOrder()
{
	std::stack< Node<T>* > nodes;

	// Обход для текущей вершины:
	// Левое поддерево - текущая вершина - правое поддерево
	Node<T>* current_node = root;
	while( !nodes.empty() || current_node != nullptr )
	{
		if( current_node != nullptr )
		{
			nodes.push( current_node );
			current_node = current_node->left;
		}
		else
		{
			current_node = nodes.top();
			nodes.pop();

			std::cout << current_node->value << " ";

			current_node = current_node->right;
		}
	}
}