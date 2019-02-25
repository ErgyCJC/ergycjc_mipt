#include "IntHashTable.h"

IntHashTable::IntHashTable(int size_) {
	size = size_;
	elements_count = 0;
	table.resize(size);
}

bool IntHashTable::Push( int value ) {
	if( IsLoadFactorCritical() ){
		RebuildTable();
	}

	int index = Hash( value, size );
	int attempt = 0;
	int	insert_index = -1;

	while( table[index].used && attempt < size ){
		
		if( table[index].value == value && !table[index].deleted ){
			return false;
		}

		if( table[index].deleted && insert_index == -1){
			insert_index = index;
		}

		++attempt;
		index = ( index + attempt ) % size;
	}

	if( insert_index != -1 ){
		table[insert_index].value = value;
		table[insert_index].deleted = false;
	}
	else {
		table[index] = Node(value, false, true);
	}

	elements_count++;
	return true;
}

bool IntHashTable::Remove( int value ) {
	int attempt = 0;
	int index = Hash( value, size );

	while( table[index].used && attempt < size ){

		if( table[index].value == value && !table[index].deleted ){
			table[index].deleted = true;
			--elements_count;
			return true;
		}

		++attempt;
		index = ( index + attempt ) % size;
	}

	return false;
}

bool IntHashTable::Find( int value ) const {
	int attempt = 0;
	int index = Hash( value, size );

	while( table[index].used && attempt < size ){

		if( table[index].value == value && !table[index].deleted ){
			return true;
		}

		++attempt;
		index = ( index + attempt ) % size;
	}

	return false;
}

bool IntHashTable::IsLoadFactorCritical() const {
	return 4 * elements_count >= 3 * size;
}

int IntHashTable::Hash( const int value, const int m ) const {
	int hash = value;
	hash += ~(hash << 16);
    hash ^=  (hash >>  5);
    hash +=  (hash <<  3);
    hash ^=  (hash >> 13);
    hash += ~(hash <<  9);
    hash ^=  (hash >> 17);
	return hash % m;
}

void IntHashTable::RebuildTable() {
	elements_count = 0;
	int old_size = size;
	size *= 2;

	std::vector<Node> old_table(std::move(table));
	table.resize(size);

	for( int i = 0; i < old_size; ++i ){
		if(old_table[i].used && !old_table[i].deleted){
			Push( old_table[i].value );
			old_table[i].used = false;
		}
		else if(old_table[i].used){
			old_table[i].used = false;
		}
	}
}