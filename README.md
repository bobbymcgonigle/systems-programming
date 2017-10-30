# Systems Programming (C)
Systems Programming Assignments

# 2015 Past exam Question
The Nucleic Acid Notation uses the letters G,C,A and T to represent the four molecules that form the subunits of deoxyribonucleic acids (DNA). the molecules combine to form a long string of molecules that can be represented as a string of characters, where the characters are selected from the symbols G,C,A,T.

Write a C routine that takes a string of symbols in standard character format and coverts it to a compressed format. Your function should have the following prototype:
unsigned char * compress_nan(char * input, int * result_length);
function should accept the string input and return a compressed version of the string (and therefore 4 times shorter). the length of the compressed string should be returned via the result_length pointer.

Secondly, write a function that takes a compressed version of the string and returns it in standard string format.

# Lab 2 - Tokeniser
Write a function with the following prototype:
int tokenise(char str[], int start, char result[]);

The function should find the next token starting at index 'start' inthe string 'str'. The token should be copied into the string 'result',
which is another character array passed to the function, so that the string is communicated back to the caller. The function returns an integer value, which should be the next position in 'str' after the returned token. Next time the function is called, this will be the next value of start. If there are no moretokens, then the returned integer value should be -1.

Please write a second tokenizer function as follows:
int tokenise_ops(char str[], int start, char result[], char operators[]);

# Lab 3 - Postfix & Infix Calculator
For the first step your program should read in a line of text containing an expression in postfix notation and write out the value
of that expression.

For example, an interaction with your program might look something like:
    mycalc> Please enter a postfix expression
    mycalc> 7 8 3 X 28 + +
    mycalc> 59
    
Once your program can compute the value of postfix expressions, extend
it further to compute the value of infix expressions. For example, if
the input is:
        ( 7 + 8 ) * 3 - 22
The output should be:
        23
        
# Lab 4 - Bit Vector Sets
Write an abstract data type (ADT) to represent sets of items, where the class of items that the set is chosen from is small and can be
mapped onto numbers zero to number of items. You should use bit vectors to represent the class. A bit vector is an array of some (usually unsigned) integer type. Each bit in each integer is used to represent the presence or absence of one item from the class of items that can belong to the set.

# Lab 5 - Bloom Filter
A Bloom filter makes extensive us of hashing functions and a bit vector set. A hashing function takes a value of some type and maps it to an integer in the range 0 to k. The simplest Bloom filters apply a single hash function to input data and insert the hashed value of the input into the bit vector set. Thereafter, if you check for membership of the item in the set it will return true. However, other items may hash to the same location with the result that the Bloom filter will also report these as members of the set.
Write an abstract data type (ADT) to represent an approximate set of
string. You should implement a Bloom filter to represent the class.

 
