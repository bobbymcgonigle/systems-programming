#include <stdlib.h>
#include <stdio.h>
#include "bloom.h"
#define TABLE_SIZE 60000
struct bloom {
	unsigned int*vector;
	int byteSize;
	int bitSize;
};
/*
	allocate memory from our inputted size
	create a new, empty bit vector set of 'size' items
	Malloc and calloc are both used to allocate memory,
	however we use calloc to initialise the allocated memory to 0
*/
struct bloom * bloom_new(int size) {
	struct bloom * theSet;
	theSet = malloc(sizeof(struct bloom)); 	//allocate number of bytes
	theSet->vector = calloc(size, sizeof(char)); //number of blocks and size of each block	
	theSet->bitSize = size;	//size = size		
	theSet->byteSize = ((size / 8) + 1);
	return theSet;
}
int djb2(char * item)
{
	unsigned int hash = 5381;
	int c;

	while ((c = *item++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash%TABLE_SIZE;
}

int jenkins(const char* word)
{
    unsigned int hash = 0;
    for (int i = 0 ; word[i] != '\0' ; i++)
    {
        hash = 31*hash + word[i];
    }
    return hash % TABLE_SIZE;
}


/* 
	check to see if a string is in the set
*/
int bloom_lookup(struct bloom * bloomTable, char * item) {

	int hash1 = jenkins(item); // first hash function returns int
	int hash2 = djb2(item); // second hash functions returns int

	int index1 = hash1 / 8; //find which secton in our vector we're looking at, eg a[i]
	int index2 = hash2 / 8; //same as above

	int bit1 = hash1 % 8; //find which actual bits in a[i] eg bit 8 
	int bit2 = hash2 % 8; //same as above

	unsigned char array_entry_1 = bloomTable->vector[index1]; //takes section from our vector
	unsigned char result_1 = (array_entry_1 >> bit1) & 1; //shift by no.of bits rightwards and & it to check if it's there

	unsigned char array_entry_2 = bloomTable->vector[index2]; //same as above except for other hash function
	unsigned char result_2 = (array_entry_2 >> bit2) & 1;

	if (result_1 == 1 && result_2 == 1)
	{
		return 1; // if they both give 1, it means that the string is PROBABLY there, although there can be false positives.
	}
	else
	{
		return 0;
	}
}


// add a string to the set
// has no effect if the item is already in the set
void bloom_add(struct bloom * this, char * item)
{

	int hash2 = djb2(item); //hash function returns int
	int hash1 = jenkins(item); //hash functions returns int
	int index1 = hash1 / 8; //find which secton in our vector we're looking at, eg a[i]
	int bitposition1 = hash1 % 8; //find which actual bits in a[i] eg bit 8 
	int index2 = hash2 / 8; //find which secton in our vector we're looking at, eg a[i]
	int bitposition2 = hash2 % 8; //find which actual bits in a[i] eg bit 8 

	if (bloom_lookup(this,item) == 0) //if not in the set add our add
	{
		this->vector[index1] = (this->vector[index1] |= (1 << bitposition1));
		this->vector[index2] = (this->vector[index2] |= (1 << bitposition2));
	}
}

// note that you cannot safely remove items from a Bloom filter

// place the union of src1 and src2 into dest
void bloom_union(struct bloom * dest, struct bloom * src1,
	struct bloom * src2)
{
	int smaller_set = (src1->byteSize < src2->byteSize ? src1->byteSize : src2->byteSize);
	for (int count = 0; count < smaller_set; count++)
	{
		dest->vector[count] = src1->vector[count] | src2->vector[count];
	}
}

// place the intersection of src1 and src2 into dest
void bloom_intersect(struct bloom * dest, struct bloom * src1,
	struct bloom * src2)
{
	int smaller_set = (src1->byteSize < src2->byteSize ? src1->byteSize : src2->byteSize);
	for (int count = 0; count < smaller_set; count++)
	{
		dest->vector[count] = src1->vector[count] & src2->vector[count];
	}
}
