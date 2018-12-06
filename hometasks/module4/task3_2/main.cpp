#include <iostream>
#include <vector>

unsigned long long pyramidsVariantsCount( const int& count )
{
	if( count < 0 ){
		return 0;
	}

	std::vector< std::vector< unsigned long long > > ways( count + 1, std::vector<unsigned long long>( count + 1, 0 ) );
	for( int i = 0; i < count + 1; ++i ){
		ways[0][i] = 1;
	}

	for( size_t current_count = 1; current_count < count + 1; ++current_count ){
		size_t bottom_layer;

		for( bottom_layer = 1; bottom_layer <= current_count; ++bottom_layer ){
			
			ways[current_count][bottom_layer] = ways[current_count][bottom_layer - 1] +
												ways[current_count - bottom_layer][bottom_layer - 1];		
		}

		for( ; bottom_layer < count + 1; ++bottom_layer ){
			ways[current_count][bottom_layer] = ways[current_count][current_count];
		}
	}
	
	return ways[count][count];
}

int main( int argc, char** argv )
{
	int blocks_count;
	std::cin >> blocks_count;
	std::cout << pyramidsVariantsCount( blocks_count ) << "\n";
	return 0;
}