// Задача 2_2
// Contest link: https://contest.yandex.ru/contest/9657/problems/2_2/
//
// Дано число N < 10^6 и последовательность пар целых чисел из [-2^31, 2^31] длиной N.
//
// Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
// Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
//
// Построить также наивное дерево поиска по ключам Xi. Равные ключи добавляйте в правое поддерево.
//
// Вычислить количество узлов в самом широком слое декартового дерева и количество узлов
// в самом широком слое наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.

#include <iostream>
#include <stack>
#include <queue>

// Структура ноды для наивного дерева
template <class T1>
struct TreeNode{
	TreeNode( T1 key, int level_ = 1 ){
        value = key;
        level = level_;
        left = right = nullptr;
    }

    ~TreeNode(){
        delete left;
        delete right;
    }

    T1 value;
    int level;

    TreeNode<T1>* left;
    TreeNode<T1>* right;
    };

// "Наивное" дерево поиска
template <class T>
class NaiveBinTree{
public:
    NaiveBinTree(){
        root = nullptr;
        levels_count = 0;
    }

    ~NaiveBinTree(){
        delete root; // Вызов деструкторов right и left с последующим удалением самой корневой вершины
    }

    void Insert( T key );

    // Нахождение максимальной ширины слоя в дереве
    int GetMaxWidth();

private:
    TreeNode<T>* root;
    int levels_count;
};

//======================//======================//======================//======================//

// Структура ноды Декартового дерева
template <class K1, class K2>
struct TreapNode{
    TreapNode( K1 x_, K2 y_ ){
        x = x_;
        y = y_;
        left = right = nullptr;
    }

    ~TreapNode(){
        delete left;
        delete right;
    }

    K1 x;
    K2 y;

    TreapNode<K1, K2>* left;
    TreapNode<K1, K2>* right;
};


// Декартово дерево
template <class T1, class T2>
class Treap{
public:

    Treap(){
        root = nullptr;
    }

    ~Treap(){
        delete root;
    }

    void Insert( T1 key, T2 priority );

	int GetMaxWidth();

private:
    TreapNode<T1, T2>* root; // Корень дерева

    // Разбивает дерево с вершиной на два по ключу key
    // Левое поддерево оказывается в left
    // Правое - в right
    void Split( TreapNode<T1, T2>* current_node, int key, TreapNode<T1, T2>*& left,  TreapNode<T1, T2>*& right );
};

//======================//======================//======================//======================//

template<class T>
void NaiveBinTree<T>::Insert( T key )
{
	if( root == nullptr ){
            root = new TreeNode<T>( key );
            levels_count = 1;
            return;
        }

        TreeNode<T>* current_node = root;
        int level = 1;

        // Проход вниз по дереву, пока не будет найдена нужная пустая листовая вершина
        while( true ){
            ++level;

            if( current_node->left == nullptr && key < current_node->value ){
                current_node->left = new TreeNode<T>( key, level );

                if( level + 1 > levels_count ){  // Обновление количества уровней в дереве
                    levels_count = level;
                }

                return;
            }
            else if( current_node->right == nullptr && key >= current_node->value ){
                current_node->right = new TreeNode<T>( key, level );

                if( level > levels_count ){  // Обновление количества уровней в дереве
                    levels_count = level;
                }

                return;
            }
            else if( current_node->left != nullptr && key < current_node->value ){
                current_node = current_node->left;
            }
            else{
                current_node = current_node->right;
            }

        }
}

template<class T>
int NaiveBinTree<T>::GetMaxWidth()
{
	int vertexes_count[ levels_count ];
        for( int i = 0; i < levels_count; ++i ){
            vertexes_count[i] = 0;
        }

        // Обход дерева
        std::stack< TreeNode<T>* > nodes;
        nodes.push( root );

        while( !nodes.empty() ){
            TreeNode<T>* current_node = nodes.top();
            nodes.pop();

            ++vertexes_count[ current_node->level - 1 ];

            if( current_node->left != nullptr ){
                nodes.push( current_node->left );
            }
            if( current_node->right != nullptr ){
                nodes.push( current_node->right);
            }
        }

        int max_width = 0;
        for( int i = 0; i < levels_count; ++i ){
            if( max_width < vertexes_count[i] ){
                max_width = vertexes_count[i];
            }
        }

        return max_width;
}

//======================//======================//======================//======================//

template<class T1, class T2>
void Treap<T1, T2>::Insert( T1 key, T2 priority )
{
	if( root == nullptr ){
		root = new TreapNode<T1, T2>( key, priority );
		return;
	}

	TreapNode<T1, T2>* current_node = root;
	TreapNode<T1, T2>* current_node_parent;
	bool is_current_node_left_child = true;

    // Спуск по дереву до тех пор, пока не будет вершины с меньшим приоритетом, чем у добавляемой
	while( current_node != nullptr && current_node->y >= priority ){
		current_node_parent = current_node;
		
		if( key < current_node->x ){
			current_node = current_node->left;
			is_current_node_left_child = true;
		}
		else{
			current_node = current_node->right;
			is_current_node_left_child = false;
		}
	}

    // Указатель на объект добавляемой вершины для удобной встаки в дерево
    // Её left и right указатели будут использованы в Split'е исходного дерева
	TreapNode<T1, T2>* inserting_node = new TreapNode<T1, T2>( key, priority );
    
    Split( current_node, key, inserting_node->left, inserting_node->right );

    if( current_node == root ){
        root = inserting_node;
    }
    else if( is_current_node_left_child ){
        current_node_parent->left = inserting_node;
    }
    else{
        current_node_parent->right = inserting_node;
    }
}

template<class T1, class T2>
void Treap<T1, T2>::Split( TreapNode<T1, T2>* current_node, int key, TreapNode<T1, T2>*& left,  TreapNode<T1, T2>*& right ){
    if( current_node == nullptr ){
		left = right = nullptr;
	}
	else if( key < current_node->x ){
        Split( current_node->left, key, left, current_node->left );
        right = current_node;
    }
    else{
        Split( current_node->right, key, current_node->right, right );
        left = current_node;
    }
}

template<class T1, class T2>
int Treap<T1, T2>::GetMaxWidth()
{
    int max_width = 0;

    // Обход дерева в ширину
    // Запись кол-ва вершин на уровне ==> удаление всех текущих вершин с добавлением их дочерних
    std::queue< TreapNode<T1, T2>* > nodes;
    nodes.push( root );

    while( !nodes.empty() ){
        if( max_width < nodes.size() ){
            max_width = nodes.size();
        }

        int tmp_width = nodes.size();
        for( int i = 0; i < tmp_width; ++i ){
            TreapNode<T1, T2>* tmp_node = nodes.front();
            nodes.pop();

            if( tmp_node->left != nullptr ){
                nodes.push( tmp_node->left );
            }
            
            if( tmp_node->right != nullptr ){
                nodes.push( tmp_node->right );
            }
        }
    }

    return max_width;
}

//======================//======================//======================//======================//

int main(int argc, char** argv){
    NaiveBinTree<int> naive_tree;
    Treap<int, int> treap;

    int pairs_count;
    std::cin >> pairs_count;
    for( int i = 0; i < pairs_count; ++i ){
        int x, y;
        std::cin >> x >> y;

        treap.Insert( x, y );
        naive_tree.Insert( x );
    }

    std::cout << treap.GetMaxWidth() - naive_tree.GetMaxWidth() << "\n";

    return 0;
}