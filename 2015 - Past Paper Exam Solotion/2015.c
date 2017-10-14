#include <stdlib.h>
#include <string.h>
#include <stdio.h>


unsigned char * compress_nan(char * input, int * result_length)
{
	int originalLength = strlen(input); //length of string input
	if(originalLength == 0 ) return NULL; //error handling
	int compressedLength = originalLength/4;
	unsigned char * compressed = malloc(sizeof(unsigned char) * compressedLength); //allocate memory in heap
	for(int i = 0 ; i < originalLength ; i++)
	{
		unsigned char symbol;
		if(input[i] =='A'){symbol = 0;}
		if(input[i]=='C'){symbol = 64;}
		if(input[i] == 'G'){symbol = 128;}
		if(input[i] == 'T'){symbol = 192;}
		symbol = symbol>>(i%4*2);	
		compressed[i/4] = compressed[i/4] | symbol;
		/*
			-  symbol equals is the code we want
			-  i%4 * 2 gets us the correct position within an 8 bit char
			-  we then shift by that amount of bits in order to place code in correct position
			-  use the logical OR operation to merge what was previously stored + what we now want to store	
		*/
	}
	result_length = &compressedLength;
	return compressed;
}
char getChar(unsigned char symbol){
	switch(symbol){
		case 0 :  return 'A';
		case 64:  return 'C';
		case 128: return 'G';
		default:  return 'T';
	}
}
char * uncompress_nan(unsigned char * input, int input_length)
{
	char * uncompressed = malloc(sizeof(char) * input_length);
	for(int i = 0 ; i < input_length i++)
	{
		unsigned char mask;
		if(i%4 == 0){mask = 192;} 	//11 00 00 00
		if(i%4 == 1){mask = 48;} 	//00 11 00 00	
		if(i%4 == 2){mask = 12;} 	//00 00 11 00
		if(i%4 == 3){mask = 3;} 	//00 00 00 11
		currentSymbol = input[i/4] & mask;
		currentSymbol = currentSymbol<<(i%4*2);
		uncompressed[i] = getChar(currentSymbol);
	}
	return uncompressed[i];
}
