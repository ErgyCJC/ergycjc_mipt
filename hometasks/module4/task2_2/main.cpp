#include <iostream>
#include <algorithm>
#include <vector>

// Заявка на переговорку [begin --- end]
struct Request
{
	int begin;
	int end;

	Request( int begin_, int end_ ) : begin( begin_ ), end( end_ ) {}
};

// Функция сравнения 
bool requestCompare( const Request& obj1, const Request& obj2 )
{
	if( obj1.end == obj2.end ){
		return obj1.begin < obj2.begin;
	}

	return obj1.end < obj2.end;
}

unsigned int validRequestsCount( const std::vector<Request>& requests )
{
	unsigned int max_count = 0;
	int last_end_time = 0;

	for( auto it = requests.begin() ; it != requests.end(); ++it ){
		if( (*it).begin >= last_end_time ){
			++max_count;
			last_end_time = (*it).end;
		}
	}

	return max_count;
}

int main( int argc, char** argv )
{
	std::vector<Request> requests; // Вектор заявок
	int begin, end; // Время начала и конца заявки

	while( std::cin >> begin >> end ){
		requests.push_back( Request( begin, end ) );
	}

	std::sort( requests.begin(), requests.end(), requestCompare );

	std::cout << validRequestsCount( requests ) << "\n";

	return 0;
}