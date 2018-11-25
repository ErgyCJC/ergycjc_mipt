#include <iostream>

typedef unsigned char byte;

void Encode()
{
	byte input_byte, prev_byte;
	int counter = -1;
	bool first_byte = true;

	while( std::cin >> input_byte ){
		if( first_byte ){
			prev_byte = input_byte;
			counter = 0;
			first_byte = false;
		}
		else if( counter == 255 ){
				std::cout << (byte)counter << prev_byte;
				counter = 0;
				prev_byte = input_byte;
		}
		else{
			if( input_byte == prev_byte ){
				++counter;
			}
			else{
				std::cout << (byte)counter << prev_byte;
				counter = 0;
				prev_byte = input_byte;
			}
		}
	}

	if( counter >= 0 ){
		std::cout << (byte)counter << input_byte;
	}
}

void Decode()
{
	byte count, value;
	while( std::cin >> count ){
		std::cin >> value;
		
		for( int i = 0; i < count + 1; ++i  ){
			std::cout << value;	
		}
	}
}

int main()
{
	// Encode();
	// Decode();
	return 0;
}