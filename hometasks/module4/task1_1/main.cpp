#include <string>
#include <iostream>
#include "hashTable.h"

int main()
{
	HashTable table;
	char command;
	std::string input_line;

	while( std::cin >> command ){
		if( command == '+' ){
			std::cin >> command;
			std::cin >> input_line;
			std::cout << ( table.Push( input_line ) ? "OK" : "FAIL" ) << "\n";
		}else if( command == '-' ){
			std::cin >> command;
			std::cin >> input_line;
			std::cout << ( table.Remove( input_line ) ? "OK" : "FAIL" ) << "\n";
		}
		else{
			std::cin >> command;
			std::cin >> input_line;
			std::cout << ( table.Find( input_line ) ? "OK" : "FAIL" ) << "\n";
		}
	}
	return 0;
}