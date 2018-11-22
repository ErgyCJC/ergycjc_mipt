// Задача 3.1
// Contest link: https://contest.yandex.ru/contest/9657/problems/3_1
//
// В одной военной части решили построить в одну шеренгу по росту.
// Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
// а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
// Однако солдаты в процессе прихода и ухода должны были всегда
// быть выстроены по росту – сначала самые высокие, а в конце – самые низкие.
// За расстановку солдат отвечал прапорщик, который заметил интересную
// особенность – все солдаты в части разного роста. Ваша задача состоит в том,
// чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого
// приходящего солдата указывать, перед каким солдатом в строе он должен становится.
// Требуемая скорость выполнения команды - O(log n).
//
// Первая строка содержит число N – количество команд (1 ≤ N ≤ 90 000).
// В каждой следующей строке содержится описание команды: число 1 и X если солдат
// приходит в строй (X – рост солдата, натуральное число до 100 000 включительно)
// и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя.
// Солдаты в строе нумеруются с нуля.
//
// На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции,
// на которую должен встать этот солдат (все стоящие за ним двигаются назад).

#include <iostream>

struct Node
{
    int key; // Значение в вершине
    int height; // Высота дерева с корнем в этой вершине
	int count; // Количество вершин в дереве с корнем в этой вершине

    Node* left;
    Node* right;
    
	Node( int key_ )
	{
		key = key_;
		height = 1;
		count = 1;
		left = right = nullptr;
	}
};

class AVLTree
{
public:

	AVLTree()
	{
		root = nullptr;
	}
	
	~AVLTree()
	{
		// Рекурсивные функции используются,
		// т.к. по условию задачи глубина рекурсии не может быть больше 17
		DeleteNode( root );
	}

	// Нахождение индекса элемента, после которого
	// будет вставлено переданное значение
	int GetPrevIndex( int key )
	{
		int index = 0;

		Node* node = root;
		while( node != nullptr ){
			if( key <  node->key ){ // Переход в левое поддерево
				node = node->left;
			}
			else{
				// Переход в правое поддерево
				index += Count( node->left ) + 1;
				node = node->right;
			}
		}

		return Count( root ) - index;
	}
	
	void Insert( int key )
	{
		root = Insert( root, key );
	}
	
	void Remove( int index )
	{
		int key = ValueByIndex( Count( root ) - index - 1 );
		root = Remove( root, key );
	}
 
private:
    Node* root;

	void DeleteNode( Node* node )
	{
		if( node != nullptr )
		{
			DeleteNode( node->left );
			DeleteNode( node->right );

			delete node;
		}
	}

	int Height( Node* node )
	{
		if (node == nullptr) {
			return 0;
		}

		return node->height;
	}
	
	void FixHeight( Node* node )
	{
		int left_height = Height( node->left );
		int right_height = Height( node->right );
		node->height = ( left_height > right_height ? left_height : right_height ) + 1;
	}
	
	int Count( Node* node )
	{
		if (node == nullptr) {
			return 0;
		}
		return node->count;
	}

	void FixCount (Node* node )
	{
		node->count = ( Count(node->left ) + Count( node->right) ) + 1;
	}
	
	// Нахождение значения элемента по индексу
	// Количество вершин в вырожденном дереве из одной вершины - 1
	// Нумерация элементов с 0!
	int ValueByIndex( int key )
	{
		Node* node = root;
		
		while (node != nullptr)
		{
			if( Count( node->left ) == key ){
				return node->key;
			}
			if( Count( node->left ) > key ){
				node = node->left;
			}
			else{
				key -= Count( node->left ) + 1;
				node = node->right;
			}
		}
	}
	
	// Малый левый поворот
	void LeftRotate( Node* a )
	{
		Node* b = a->right;
		a->right = b->left;
		b->left = a;
		
		FixHeight( a );
		FixCount( a );
		
		FixHeight( b );
		FixCount( b );
	}
	
	// Малый правый поворот
	void RightRotate( Node* a )
	{
		Node* b = a->left;
		a->left = b->right;
		b->right = a;

		FixHeight( a );
		FixCount( a );
		
		FixHeight( b );
		FixCount( b );
	}
	
	int BalanceFactor( Node* node )
	{
		return Height( node->left ) - Height( node->right );
	}

	Node* Insert( Node* node, int key )
	{
		if( node == nullptr ){
			node = new Node( key );
		}
		else if( key < node->key ){
			node->left = Insert( node->left, key );
		}
		else{
			node->right = Insert( node->right, key );
		}

		return Balance(node);
	}

	// Перебалансировка вершины
	Node* Balance( Node* node )
	{
		FixHeight( node );
		FixCount( node );

		Node* result_node = node;
		if( BalanceFactor(node) == 2 ){ // Требуется правый поворот

			if(BalanceFactor(node->left) < 0 ){ // Требуется малый правый поворот
				result_node = node->left;
				node->left = node->left->right;
				LeftRotate( result_node );
			}

			result_node = node->left;
			RightRotate( node );
		}
		else if( BalanceFactor(node) == -2 ){ // Требуется левый поворот

			if( BalanceFactor(node->right) > 0 ){ // Требуется большой левый поворот
				result_node = node->right;
				node->right = node->right->left;
				RightRotate( result_node );
			}

			result_node = node->right;
			LeftRotate( node );
		}

		return result_node; // Возврат строго корня перебалансированной верхушки поддерева
	}
	
	// Нахождение указателя на минимальную ноду в дереве
	Node* FindMinNode( Node* node ){
		if (node->left == nullptr){
			return node;
		}

		return FindMinNode( node->left );
	}
	
	// Удаление связей с минимальной вершиной в дереве
	Node* RemoveMinNode( Node* node )
	{
		if( node->left == nullptr ){
			return node->right;
		}
		
		node->left = RemoveMinNode(node->left);
		return Balance( node );
	}

	Node* Remove( Node* node, int key )
	{
		if( node == nullptr ){
			return node;
		}

		if( key < node->key ){ // Переход в левое поддерево
			node->left = Remove( node->left, key );
		}
		else if( key > node->key ){ // Переход в правое поддерево
			node->right = Remove( node->right, key );
		}
		else{ // Найден удаляемый элемент
			// Сохранение указателей на правое и левое поддерево
			// Т.к. корень поддерева будет удалён
			Node* left_subtree = node->left;
			Node* right_subtree = node->right;
			
			delete node;
			
			if( right_subtree == nullptr ){
				return left_subtree;
			}

			// Подъём минимальной ноды поддерева в его корень
			Node* min_node = FindMinNode( right_subtree );
			min_node->right = RemoveMinNode( right_subtree );
			min_node->left = left_subtree;
			
			return Balance( min_node );
		}

		return Balance( node );
	}

};

int main( int argc, char** argv )
{
    AVLTree line;
    int count, command, value;

    std::cin >> count;
    for( int i = 0; i < count; ++i ){
        std::cin >> command >> value;
        
		if( command == 1 ){
            std::cout << line.GetPrevIndex( value ) << "\n";
            line.Insert( value );
        }
		else{
            line.Remove( value );
        }
    }
    return 0;
}