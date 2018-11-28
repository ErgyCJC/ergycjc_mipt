#ifndef __HASH_TABLE_HEADER__
#define __HASH_TABLE_HEADER__

#include <vector>
#include <string>

struct Node
{
	int hash;
	std::string line;

	Node( int hash_, std::string line_ ): hash( hash_ ), line( line_ ) {} // default doesn't work
};

class HashTable
{
public:

	HashTable( int size = 8, int size_log = 3 ); // solved

	~HashTable(); // solved

	bool Push( std::string& line ); // solved

	bool Remove( std::string& line );

	bool Find( std::string& line ); // solved

private:

	int elements_count;
	int current_m;
	int size;
	int size_log;

	std::vector< Node* >* table; // Ptr для не-копирования
	std::vector< bool >* removed;
	std::vector< int > prime_dividers; // Список простых чисел

	bool IsLoadFactorCritical(); // Превышает ли load factor значение 3/4 ( из задания ) | solved

	int StringHash( std::string& line ); // solved

	int Probe( int i, std::string& line, int prev_probe = 0 ); // solved

	void IncreaseSize(); // solved

};

#endif