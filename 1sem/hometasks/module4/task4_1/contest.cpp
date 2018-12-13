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
	std::vector<int> parents;

	void setHeights( int index );

	void setRootWays( int index );
};

//========================//========================//========================//========================//

Graph::Graph( int count )
{
	connections.resize( count );
	
	heights.resize( count, 0 );
	rootWays.resize( count, 0 );
	parents.resize( count, -1 );
}

void Graph::add( int index1, int index2 )
{
	connections[index1].push_back( index2 );
	connections[index2].push_back( index1 );

	parents[index2] = index1;	
}

void Graph::putOutDistances( std::ostream& out_stream )
{
	setHeights( 0 );
	setRootWays( 0 );

	for( int i = 0; i < connections.size(); ++i ){
		out_stream << std::max( rootWays[i], heights[i] ) << "\n";
	}
}

void Graph::setHeights( int index )
{
	for( int i = 0; i < connections[index].size(); ++i ){
		if( connections[index][i] != parents[index] ){
			setHeights( connections[index][i] );

			if( heights[ connections[index][i] ] + 1 > heights[index] ){
				heights[index] = heights[ connections[index][i] ] + 1;
			}
		}
	}
}

void Graph::setRootWays( int index )
{
	int maxSubHeight1 = -1, maxSubIndex1;
    int maxSubHeight2 = -1, maxSubIndex2;

    for( int i = 0; i < connections[index].size(); ++i ){
		int next_index = connections[index][i];

        if( next_index != parents[index] ){
			if( maxSubHeight1 <= heights[next_index] + 1 ){
				maxSubIndex2 = maxSubIndex1;
				maxSubHeight2 = maxSubHeight1;
				
				maxSubIndex1 = next_index;
				maxSubHeight1 = heights[next_index] + 1;
			}
			else if( maxSubHeight2 <= heights[next_index] + 1 ){
				maxSubHeight2 = heights[next_index] + 1;
				maxSubIndex2 = next_index;
			}
		}
    }

    for( int i = 0; i < connections[index].size(); ++i ){
		int next_index = connections[index][i];

		if( next_index != parents[index] ){
			if (next_index == maxSubIndex1) {
				rootWays[next_index] = std::max(rootWays[index], maxSubHeight2) + 1;
			} else {
				rootWays[next_index] = std::max(rootWays[index], maxSubHeight1) + 1;
			}

			setRootWays( next_index );
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