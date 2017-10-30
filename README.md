# systems-programming
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
    
 
