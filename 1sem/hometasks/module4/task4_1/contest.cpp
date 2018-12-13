#include <vector>
#include <iostream>
#include <stack>
#include <cmath>
#include <cstdlib>

class Graph
{
public:
	Graph( int count );

	void add( int index1, int index2 );

	void putOutDistances( std::ostream& out_stream );

private:
	// Матрица смежности
	std::vector< std::vector<int> > connections;

	std::vector<int> heights;
	std::vector<int> rootWays;

	void setHeights( int index, int par );

	void setRootWays( int index, int par );
};

//========================//========================//========================//========================//

Graph::Graph( int count )
{
	connections.resize( count );
	
	heights.resize( count, 0 );
	rootWays.resize( count, 0 );
}

void Graph::add( int index1, int index2 )
{
	connections[index1].push_back( index2 );
	connections[index2].push_back( index1 );
}

void Graph::putOutDistances( std::ostream& out_stream )
{
	setHeights( 0, -1 );
	setRootWays( 0, -1 );

	for( int i = 0; i < connections.size(); ++i ){
		out_stream << std::max( rootWays[i], heights[i] ) << "\n";
	}
}

void Graph::setHeights( int index, int par )
{
	for( int i = 0; i < connections[index].size(); ++i ){
		if( connections[index][i] != par ){
			setHeights( connections[index][i] );
		}
	}
}

//========================//========================//========================//========================//

int main( int argc, char** argv )
{
	int count, index1, index2;
	std::cin >> count;

	Graph tree( count );
	for( int i = 0; i < count - 1; ++i ){
		std::cin >> index1 >> index2;
		tree.add( index1, index2 );
	}

	tree.putOutDistances( std::cout );
	return 0;
}