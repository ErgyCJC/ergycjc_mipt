#include <vector>
#include <iostream>
#include <algorithm>

struct Human
{
	int weight;
	int power;

	Human( int weight_, int power_ ) : weight( weight_ ), power( power_ ) {}
};

bool compareHumans( const Human& a, const Human& b )
{
	if( a.weight == b.weight ){
			return a.power < b.power;
		}

	return a.weight < b.weight;
}

unsigned int countTowerHeight( std::vector< Human >& people )
{
	if( people.empty() ){
		return 0;
	}

	std::sort( people.begin(), people.end(), compareHumans );

	unsigned int result_height = 1;
	unsigned int weightToHold = people.at(0).weight;

	for( size_t i = 1; i < people.size(); ++i ){
		if( people.at(i).power >= weightToHold ){
			weightToHold += people.at(i).weight;
			++result_height;
		}
	}

	return result_height;
}

int main( int argc, char** argv )
{
	std::vector< Human > people;
	int weight, power;

	while( std::cin >> weight >> power ){
		people.push_back( Human( weight, power ) );
	}

	std::cout << countTowerHeight( people ) << "\n";
	return 0;
}