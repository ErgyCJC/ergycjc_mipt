#include "Huffman.h"

void Encode(IInputStream& original, IOutputStream& compressed) 
{
	byte input_byte, prev_byte;
	int counter = -1;
	bool first_byte_flag = true;

	while( original.Read( input_byte ) ){
		if( first_byte_flag ){
			prev_byte = input_byte;
			counter = 0;
			first_byte_flag = false;
		}
		else if( counter == 255 ){
				compressed.Write( (byte)counter );
				compressed.Write( prev_byte );

				counter = 0;
				prev_byte = input_byte;
		}
		else{
			if( input_byte == prev_byte ){
				++counter;
			}
			else{
				compressed.Write( (byte)counter );
				compressed.Write( prev_byte );

				counter = 0;
				prev_byte = input_byte;
			}
		}
	}

	if( counter >= 0 ){
		compressed.Write( (byte)counter );
		compressed.Write( input_byte );
	}
}

void Decode(IInputStream& compressed, IOutputStream& original) 
{ 
	byte count, value;
	while( compressed.Read( count ) ){
		compressed.Read( value );
		
		for( int i = 0; i < count + 1; ++i  ){
			original.Write( value );
		}
	}
}
