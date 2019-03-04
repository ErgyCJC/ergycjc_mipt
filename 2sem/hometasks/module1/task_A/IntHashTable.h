#include <vector>
#include <utility>

class IntHashTable {
public:
	IntHashTable( int size_ = 8 );

	bool Push( int value );

	bool Remove( int value );

	bool Find( int value ) const;

private:
	struct Node {
    	int value;
    	bool deleted;
		bool used;

		Node() : deleted(false), used(false) {}

		Node(int value_, bool deleted_, bool used_) : value( value_ ), deleted( deleted_ ), used(used_) {}
	};

	std::vector<Node> table;
	int size;
	int elements_count;

	bool IsLoadFactorCritical() const;

	int Hash( const int value, const int m) const;
	
	void RebuildTable();
};