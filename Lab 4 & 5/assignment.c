#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloom.h"
#include "bitset.h"


int tokenise_ops(char str[], int start, char result[]) {//tokenise from previous lab
	int i;
	int i2 = 0;

	for (i = start; str[i] != ' '; i++) {
		result[i2] = str[i];
		i2++;
		if (str[i] == '\0') {//if string is at its end, terminate
			return -1;
		}
	}
	while (str[i] == ' ') {//proceeds to next character
		i++;
	}

	result[i2] = '\0';
	return i;
}
void bitset()
{
    char buffer1 [1024];                  // Gather the firstLine from the user and add to the bitset
    printf("Write the first word:\n");	 
    fgets(buffer1, 1024, stdin);
    struct bitset * firstWord = bitset_new(1024);
    
    addCharacters(buffer1, firstWord);
    
    
    char buffer2 [1024];                  // Gather the secondLine from the user
    printf("Write the second word:\n");
    fgets(buffer2, 1024, stdin);
   struct  bitset * secondWord = bitset_new(1024);
    addCharacters(buffer2, secondWord);
    
    
    printf("\nThe first word that you inputted is: %s\n", buffer1);
    printf("\nThe second word that you inputted is: %s\n", buffer2);
    
   
    //----------------------------------------------------------------

   struct bitset * intersectSet = bitset_new(1024);
    bitset_intersect(intersectSet, firstWord, secondWord);
    int count;
    printf("These are the characters the two words have in common: ");
    for (count = 0; count <256; count ++){
        if(bitset_lookup(intersectSet, count) == 1){
            printf("%c ", count);
        }
    }
    
    //----------------------------------------------------------------
    
    printf("\n\n");

    struct bitset * unionSet = bitset_new(1024);
    
    bitset_union(unionSet, firstWord, secondWord);
    printf("These are all the characters contained in the two words: ");
    for (count = 0; count < 256; count ++)
    {
        if(bitset_lookup(unionSet, count) == 1)
        {
            printf("%c ", count);
        }
    }
    printf("\n");
}
void bloom(char file1[], char file2[])
{
    struct bloom * seen;
    seen = bloom_new(100000); //make struct
 
    struct bloom* written;
    written = bloom_new(100000); //make struct
 
    char answer1[1024];
    char answer2[1024];
 
    FILE *pFile;
 
    char line[1024];
 
    pFile = fopen(file1,"r");

        while (fgets(line, sizeof(line), pFile) != NULL)
        {
            int start = tokenise_ops(line, 0, answer1);
            while (start != -1)
            {   
                    bloom_add(seen, answer1);       
                    start = tokenise_ops(line, start, answer1);
            }
        }
        fclose(pFile);
 
        FILE *newfile;
        newfile= fopen(file2,"r"); 
        char line2[1024];
 
        while(fgets(line2, sizeof(line2), newfile) != NULL)
        {
            int start2 = tokenise_ops(line2, 0, answer2);
            while(start2 != -1)
            {
                if(bloom_lookup(seen,answer2) == 1) //if the current string is inside the seen bitset 
                {
                    if(bloom_lookup(written,answer2) == 0) //also check if it's been written before, it hasnt been added already
                    {
                        bloom_add(written, answer2); //add to written & print out
                        puts(answer2);  
                    }
                }
                start2 = tokenise_ops(line2, start2, answer2);
            }
        }
        fclose(newfile);
}
int main(int argc, char **argv)
{
	if (strcmp(argv[1],"bloom") == 0) //if first argument is bloom
	{
		bloom(argv[2],argv[3]); //call bloom and give two text files as parameters
	}
	else if(strcmp(argv[1],"bitset") == 0)
	{
		bitset(); //call bitset
	}
	else
	{
		puts("Not a proper input, try again");
	}

}
