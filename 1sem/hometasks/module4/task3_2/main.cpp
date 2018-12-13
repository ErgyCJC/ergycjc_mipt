// Задача 3.2
// Contest link: https://contest.yandex.ru/contest/10866/problems/3_2
//
// Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
// Каждый следующий уровень короче предыдущего.

#include <iostream>
#include <vector>

unsigned long long pyramidsVariantsCount( const int& count )
{
	if( count < 0 ){
		return 0;
	}

	// Кол-во способов построить пирамидки из n кубиков
	std::vector< std::vector< unsigned long long > > ways( count + 1, std::vector<unsigned long long>( count + 1, 0 ) );
	// Для любого кол-ва кубиков существует только один способ составить пирамидку из 0 кубиков
	for( int i = 0; i < count + 1; ++i ){
		ways[0][i] = 1;
	}

	// bottom_count - кол-во кубиков в нижнем слое
	// using_count - используемое на данный момент кол-во кубиков для построения пирамидки
	for( size_t bottom_count = 1; bottom_count < count + 1; ++bottom_count ){
		size_t using_count;

		for( using_count = 1; using_count <= bottom_count; ++using_count ){
			
			ways[bottom_count][using_count] = ways[bottom_count][using_count - 1] +
												ways[bottom_count - using_count][using_count - 1];		
		}

		for( ; using_count < count + 1; ++using_count ){
			ways[bottom_count][using_count] = ways[bottom_count][bottom_count];
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