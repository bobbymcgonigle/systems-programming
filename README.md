# systems-programming
Systems Programming Assignments

# 2015 Past exam Question
The Nucleic Acid Notation uses the letters G,C,A and T to represent the four molecules that form the subunits of deoxyribonucleic acids (DNA). the molecules combine to form a long string of molecules that can be represented as a string of characters, where the characters are selected from the symbols G,C,A,T.

Write a C routine that takes a string of symbols in standard character format and coverts it to a compressed format. Your function should have the following prototype:
unsigned char * compress_nan(char * input, int * result_length);
function should accept the string input and return a compressed version of the string (and therefore 4 times shorter). the length of the compressed string should be returned via the result_length pointer.

Secondly, write a function that takes a compressed version of the string and returns it in standard string format.
