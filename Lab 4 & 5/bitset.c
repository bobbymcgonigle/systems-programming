#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"

#define MAX_STRING 256

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

struct bitset{
    unsigned char * vector;
    int size_bits;
    int size_bytes;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

struct bitset * bitset_new(int size){
    struct bitset * theSet = malloc(sizeof(struct bitset));
    theSet->vector = calloc(size, sizeof(char));
    theSet->size_bits = size;
    theSet->size_bytes = ((size/8)+1);
    return theSet;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

int bitset_lookup(struct bitset*theSet, int item){
    int array_index = item/8;
    int bit_index = item%8;
    
    if(array_index > theSet->size_bytes)
    {
        return -1;
    }

    unsigned char array_entry =  theSet->vector[array_index];
    unsigned char result = (array_entry >> bit_index)&1;
    return result;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

int bitset_add(struct bitset*theSet, int item){
    int array_index = item/8;
    int bit_index = item%8;
    
    if(bitset_lookup(theSet, item) == -1)
    {
        return 0;
    }
    
    if(bitset_lookup(theSet, item) != 0)
    {
        return 0;
    }
    theSet->vector[array_index] = (theSet->vector[array_index] | (1 << bit_index));
    return 1;
}

//------------------------------------------------------------------------------
// Function tokenises the characters and adds to bitset
//------------------------------------------------------------------------------

void addCharacters(char str[],struct bitset * wordSet){
    int pos = 0;
    unsigned char character;
    
    while (1){                          
        if(str[pos] == ' ')               
            pos++;
            continue;
        }
        else if(str[pos] == '\0')          
        {
            break;
        }
        else                                
        {
            character = (unsigned char)(str[pos]);
            bitset_add(wordSet, character);
            pos++;
        }
    }
}

//------------------------------------------------------------------------------
// Function tokenises the characters and adds to bitset
//------------------------------------------------------------------------------

void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2){
    int smaller_set = (src1->size_bytes < src2->size_bytes ? src1->size_bytes:src2->size_bytes);
    for (int count = 0; count < smaller_set ; count++)
    {
        dest->vector[count]=src1->vector[count]&src2->vector[count];
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

void bitset_union (struct bitset*dest, struct bitset*src1, struct bitset*src2){
    
    int smaller_set = (src1->size_bytes < src2->size_bytes ? src1->size_bytes:src2->size_bytes);
    for (int count = 0 ; count < smaller_set; count++)
    {
        dest->vector[count] = src1->vector[count] | src2->vector[count];
    }
}

