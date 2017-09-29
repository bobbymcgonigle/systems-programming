#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
const int MAX = 1024;
const int MAX_STRING = 256;
bool operator = false;
 
 struct stack
    {
        double values[1024];
        int top;
    };
 
struct stack * new_stack()
    {
        struct stack * new;
        new = malloc(sizeof(struct stack));     // give some memory for the stack
        new ->top=0;
        return new;
    }

int stack_empty(struct stack * this)
    {
        if(this->top == 0)
            {
                return 1;
            }
        else
            {
                return 0;
            }
    }

double stack_pop(struct stack * this)
{
    double numberToBePopped;
    this->top = this->top-1;
    numberToBePopped = this->values[this->top];
    return numberToBePopped;
}
 
void stack_push(struct stack * this, double item)
    {
        if(this->top < MAX-1) //if top of stack is less than max size of stack -1
	{
        	this->values[this->top] = item;
       		this->top = this->top + 1;
	}
    }
 
int tokenise(char str[], int start, char result[]){
    int i;
    int i2 = 0;
 
    for (i = start; str[i] != ' '; i++){
        result[i2] = str[i];
        i2++;
        if(str[i]=='\0'){ //if string is at its end, terminate
            return -1;
        }
    }
    while(str[i]==' '){ //proceeds to next character
        i++;
    }
 
    result[i2] = '\0';
    return i;
}
int precedence(char x)
{
   if(x == '(')
      return(1);
   if(x == '^')
      return(0);
   if(x == '+' || x == '-')
      return(3);
   if(x == '*' || x == '/' || x == '%')
      return(2);
   return(4);
}
int empty(struct stack *s)
{
    if(s->top==0)
 return(1);
    else 
 return(0);
}
    int numlen(int n) {
        if (n < 0) n = -n;
        int i = 1;
        while ((n/=10)>0)
            i++;
        return i;
    }
int tokenise_ops(char str[], int start, char result[], char operators[]){
    
    int i = 0;  
    if(operator)
    {
        for(int j = 0; j < 7; j++)
        {
            if(str[start] == operators[j])  //234567    // +'\0' 3455667
            {
                result[i] = str[start];
                i++;
                result[i] = '\0';
                operator = false;
                return ++start;
            }
        }
    }  
    while(str[start] != '\0')
    {
        
        for(int j = 0; j < 7; j++)
        {
            if(str[start] == operators[j])      //23+ 4
                
            {
                operator = true;
                result[i] = '\0';
                return start;
            }
        }
        
        if(str[start] != ' ')
        {
            result[i] = str[start];
            i++;
            start++;
        }
        else        {
            result[i] = '\0';
            return ++start;
        }
        
    }
    
    result[i] = '\0';
    return -1;
}
 void infix_to_postfix(char infix[], struct stack * this, char postfix[])
{
   bool firstCompare = true;
   int first = 0;
   int indexforfirst = 0; 
	char operators[] = {'+','-','*','/','^','(',')'};
    char x;
    int i,j;    //i-index of infix,j-index of postfix
    j=0;
    char result[MAX_STRING];
	int index = 0;
    while (index != -1){
    index = tokenise_ops(infix, index, result, operators);
    double determine = atof(result);
        if(determine != 0)
        {
	  postfix[j++] = ' ';
       	  int index2=0;
      	  while(result[index2] != '\0')
          {
              postfix[j++] = result[index2];
              index2++;
          }
	first = 1;
	}
     
        else if(result[0] == '+' || result[0] == '*' || result[0]== '^' || result[0] == '-')
	{
	int value;
	char temp;
	temp = stack_pop(this);
	value = precedence(temp);
	stack_push(this, temp);
           while(precedence(result[0]) >= value &&!empty(this))
               {
		   postfix[j++] = ' ';
		   x = stack_pop(this);
                   postfix[j++]= x;
               }
		stack_push(this,result[0]);
		 if (result[0]=='(')
       		 {
               stack_push(this,result[0]);
       		 }
        }
        else if(result[0]==')')
		{
	        while(this->values[this->top] != '(' &&!empty(this))
            {
		postfix[j++] = ' ';
                x = stack_pop(this);
                postfix[j++] = x;
                
            }
            if(!empty(this))
            {
            stack_pop(this);
            }
		}
}



	while(!empty(this))
    {
	postfix[j] = ' ';
	j++;
        x=stack_pop(this);
        postfix[j++]=x;
    }
	int m = 0;
	while(m < 30)
	{
	    if(postfix[m] == '\0')
		{
		postfix[m] = ' ';
		}
	    m++;
	}
	postfix[j++] = '\0';
	printf("FINAL STRNIG STRING: %s", postfix);

}
int power(int base, int powerRaised)
{
    if (powerRaised != 1)
        return (base*power(base, powerRaised-1));
    else
        return 1;
}
int main(){
 char buffer[MAX_STRING];
    printf("Write a mathematic equation plz :) :\n");
    fgets(buffer, MAX_STRING, stdin); //reads input
    double num1;
    double num2;
    double answer;
    char postfix[MAX_STRING];
 
    struct stack * list2;
    list2 = new_stack();
    struct stack * list;
    list = new_stack();
    char string[] = " 56 + 5 + 5";
    infix_to_postfix(buffer,list2, postfix);

    char result[MAX_STRING];
    int index = 0;
    while (index != -1){
        index = tokenise(postfix, index, result);
        double determine = atof(result);
        if (determine != 0)
        {
            stack_push(list, determine);
        }
        else
       {
            num1 = stack_pop(list);
            num2 = stack_pop(list);
 
            switch (result[0]) //switch statement that uses non operator stack and switch 		    statement to detect which operation to perform.
            {
	    case '*':
                answer = num1*num2;
                stack_push(list, answer);
	    break;
 
            case '/':
                answer = (num1/num2);
                stack_push(list, answer);
            break;
 
            case '+':
                answer = num1+num2;
                stack_push(list, answer);
	    break;
	    case '^':
	    answer = power(num2, num1+1);
	    stack_push(list, answer);
	}
 
            if(result[0] == '-')
            {
                answer = num1-num2;
                stack_push(list, answer);
            }
        }
    }
	printf("\nANSWER IS: %f\n", answer);
     
    return 0;
}
