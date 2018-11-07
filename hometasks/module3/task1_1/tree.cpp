#include "tree.h"

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
		if( current_node->left == nullptr && key < current_node->value )
		{
			current_node->left = new Node<T>;
			current_node->left->value = key;
			return;
		}
		else if( current_node->right == nullptr && key >= current_node->value )
		{
			current_node->right = new Node<T>;
			current_node->right->value = key;
			return;
		}
		else if( current_node->left != nullptr && key < current_node->value )
		{
			current_node = current_node->left;
		}
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