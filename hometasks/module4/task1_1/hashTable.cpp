#include "hashTable.h"

HashTable::HashTable( int size_, int size_log_ )
{
	size = size_;
	size_log = size_log_;

	table = new std::vector< Node* >( size, nullptr );
	removed = new std::vector< bool >( size, true );
	
	// Простые числа, меньшие 2^i, где i - индекс выбранного числа ( 1 и 2 - исключения, они бесполезны )
	prime_dividers = std::vector< int >{ 1, 2, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191,
		16381, 32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393,
		67108859, 134217689, 268435399, 536870909, 1073741789, 2147483647 };

	current_m = prime_dividers[size_log];
	elements_count = 0;
}

HashTable::~HashTable()
{
	for( int i = 0; i < table->size(); ++i ){
		delete table->at(i);
	}

	delete table;
	delete removed;
}

int HashTable::Probe( int i, std::string& line, int prev_probe )
{
	if( i == 0 ){
		return StringHash( line );
	}

	return ( prev_probe + i ) % size; // size принимает значения степеней двойки
}

int HashTable::StringHash( std::string& line )
{
	int hash = 0;

	for( int i = 0; i < line.size(); ++i ){
		hash = ( hash + line[i] ) % current_m;
	}

	return hash;
}

bool HashTable::IsLoadFactorCritical()
{
	return 4 * elements_count >= 3 * size; // alpha >= 3/4 ?
}

void  HashTable::IncreaseSize()
{
	size *= 2;
	++size_log;
	current_m = prime_dividers[size_log];

	std::vector< Node* >* old_table = table;
	table = new std::vector< Node* >( size );

	delete removed;
	removed = new std::vector< bool >( size, true );

	for( int i = 0; i < old_table->size(); ++i ){
		Push( old_table->at(i)->line );
		delete old_table->at(i);
	}

	delete old_table;
}

bool HashTable::Push( std::string& line )
{
	int attempt = 0;
	int hash = StringHash( line );
	int index = Probe( attempt, line );

	while( !removed->at(index) ){
		if( table->at(index)->hash == hash ){
			return false;
		}

		index = Probe( attempt + 1, line, index );
	}

	table->at(index) = new Node( StringHash( line ), line );
	++elements_count;

	if( IsLoadFactorCritical() ){
		IncreaseSize();
	}

	return true;
}

bool HashTable::Remove( std::string& line )
{
	int attempt = 0;
	int hash = StringHash( line );
	int index = Probe( attempt, line );

	while( table->at( index ) != nullptr ){
		if( table->at( index ) != nullptr ){
			if( removed->at( index ) ){
				return false;
			}
			else{
				removed->at( index ) = true;
				--elements_count;
				return true;
			}
		}

		index = Probe( attempt + 1, line, index );
	}

	return false;
}

bool HashTable::Find( std::string& line )
{
	int attempt = 0;
	int hash = StringHash( line );
	int index = Probe( attempt, line );

	while( table->at( index ) != nullptr ){
		if( table->at( index )->hash == hash ){
			if( removed->at( index ) ){
				return false;
			}
			else{
				return true;
			}
		}

		index = Probe( attempt + 1, line, index );
	}

	return false;
}