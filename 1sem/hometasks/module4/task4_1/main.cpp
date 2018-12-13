#include <vector>
#include <iostream>
#include <stack>
#include <cmath>
#include <cstdlib>

struct Node
{
	int index;
	int parent;
	
	std::vector< int > connections;

	Node( int i_, int parent_ = -1 ) : index( i_ ), parent( parent_ ) {}
};

class Tree
{
public:
	Tree( int count );

	~Tree();

	void add( int index1, int index2 );

	void putOutDistances( std::ostream& outStream );

private:
	std::vector< Node* > tree;
	std::vector< int > heights;
	std::vector< int > distances;

	void setHeights( int node );

	void resetHeights( int node, int callingNode );
};

//========================//========================//========================//========================//

Tree::Tree( int count )
{
	tree.resize( count, nullptr );
	tree[0] = new Node( 0 );

	heights.resize( count, 0 );
	distances.resize( count, 0 );
}

Tree::~Tree()
{
	std::stack< int > nodes;
	
	if( tree[0] != nullptr )
	nodes.push( 0 );

	while( !nodes.empty() ){
		int node = nodes.top();
		nodes.pop();

		for( int i = 0; i < tree[node]->connections.size(); ++i ){
			if( tree[node]->connections[i] != tree[node]->parent ){
				nodes.push( tree[node]->connections[i] );
			}
		}

		delete tree[node];
	}
}

void Tree::add( int index1, int index2 )
{
	if( index1 > index2 ){
		std::swap( index1, index2 );
	}

	tree[index2] = new Node( index2, index1 );
	tree[index2]->connections.push_back( index1 );
	tree[index1]->connections.push_back( index2 );
}

void Tree::setHeights( int node )
{
	for( int i = 0; i < tree[node]->connections.size(); ++i ){
		if( tree[node]->parent != tree[node]->connections[i] ){
			setHeights( tree[node]->connections[i] );
			
			if( heights[ tree[node]->connections[i] ] + 1 > heights[node] ){
				heights[node] = heights[ tree[node]->connections[i] ] + 1;
			}
		}
	}
}

// node - текущая вершина
// callingNode - вершина, которая вызвала эту итерацию DFS
void Tree::resetHeights( int node, int callingNode )
{
	// Сведения о двух самых больших поддеревьях
	int maxSubHeight1 = -1, maxSubHeightIndex1;
	int maxSubHeight2 = -1, maxSubHeightIndex2;

	// Поиск двух самых удалённых поддеревьев для текущей вершины
	for( int i = 0; i < tree[node]->connections.size(); ++i ){
		if( tree[node]->connections[i] != callingNode ){
			
			if( heights[node] + 1 >= maxSubHeight1 ){
				maxSubHeight2 = maxSubHeight1;
				maxSubHeightIndex2 = maxSubHeight1;

				maxSubHeightIndex1 = node;
				maxSubHeight1 = heights[node] + 1;
			}
			else if( heights[node] + 1 >= maxSubHeight2 ){
				maxSubHeightIndex2 = node;
				maxSubHeight2 = heights[node] + 1;
			}
		}
	}

	for( int i = 0; i < tree[node]->connections.size(); ++i ){
		if( tree[node]->connections[i] != callingNode ){
			if( tree[node]->connections[i] == maxSubHeightIndex1 ){
				distances[node] = std::max( maxSubHeight2, distances[node] ) + 1;
			}
			else{
				distances[node] = std::max( maxSubHeight1, distances[node] ) + 1;
			}

			resetHeights( tree[node]->connections[i], node );
		}
	}
}

void Tree::putOutDistances( std::ostream& outStream )
{
	setHeights( 0 );
	resetHeights( 0, -1 );

	for( int i = 0; i < distances.size(); ++i ){
		outStream << std::max( distances[i], heights[i] ) << "\n";
	}
}

//========================//========================//========================//========================//

int main( int argc, char** argv )
{
	int count, index1, index2;
	std::cin >> count;

	Tree tree( count );
	for( int i = 0; i < count - 1; ++i ){
		std::cin >> index1 >> index2;
		tree.add( index1, index2 );
	}

	tree.putOutDistances( std::cout );
	return 0;
}