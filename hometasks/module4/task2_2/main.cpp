// Задача 2.2
// Contest link: https://contest.yandex.ru/contest/10866/problems/2_2
//
// В большой IT-фирме есть только одна переговорная комната.
// Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
// Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
// Число заявок <= 100000.
//
// Вход содержит только пары целых чисел — начала и концы заявок.
// Выход должен содержать натуральное число — максимальное число заявок.

#include <iostream>
#include <algorithm> // std::sort
#include <vector>

// Заявка на переговорку [begin --- end]
struct Request
{
	int begin;
	int end;

	Request( int begin_, int end_ ) : begin( begin_ ), end( end_ ) {}
};

// Функция сравнения для сортировки заявок в порядке невозрастания времени окончания
bool requestCompare( const Request& obj1, const Request& obj2 )
{
	if( obj1.end == obj2.end ){
		return obj1.begin < obj2.begin;
	}

	return obj1.end < obj2.end;
}

// Максимальное кол-во заявок, которые можно удовлетворить
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