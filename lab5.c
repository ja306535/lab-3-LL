//Jalil Fountain
//This lab goes over stacks and implementing its operations
// arap guha
// 6/20/07
// Written in COP 3502 to illustrate an array implementation of a stack.
//modified by Tanvir Ahmed 6/1/2020
//Modified by Adam Betinsky on 2/3/2025 to save time while doing Lab #5
//Lab #5: Stack Implementation Skeleton Code
//UPDATED ON 2/4/2025 to allow for a character stack instead of an integer stack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //needed for isdigit
// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.
#define SIZE 100
#define EMPTY -1
struct stack {
char items[SIZE];
int top;
};
//Provided functions
void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
char peek(struct stack* stackPtr);
void print_stack(struct stack* stackPtr);
//---------------------------------------------
//Functions you need to complete (in addition to main)
int checkBalance(char exp[]);
int priority(char ch);
int isOperator(char ch);
char *infixToPostfix(char infix[]);
int isParentheses(char ch1);

int main(void) {
int ch;
char exp[SIZE], c;
int valid;
printf("\nEnter Expression: ");
scanf("%[^\n]s",exp);
printf("Your input expression: %s\n", exp);
valid = checkBalance(exp);
if(valid)
{
char * postfix = infixToPostfix(exp);
printf("The postfix is: %s\n", postfix);
free(postfix);
}
return 0;
}
void initialize(struct stack* stackPtr) {
stackPtr->top = -1;
}
// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack* stackPtr, char value) {
// Check if the stack is full.
if (full(stackPtr))
return 0;
// Add value to the top of the stack and adjust the value of the top.
stackPtr->items[stackPtr->top+1] = value;
(stackPtr->top)++;
return 1;
}
// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) {
return (stackPtr->top == SIZE - 1);
}
// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr) {
return (stackPtr->top == -1);
}
// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack* stackPtr) {
char retval;
// Check the case that the stack is empty.
if (empty(stackPtr))
return EMPTY;
// Retrieve the item from the top of the stack, adjust the top and return
// the item.
retval = stackPtr->items[stackPtr->top];
(stackPtr->top)--;
return retval;
}
// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char peek(struct stack* stackPtr) {
// Take care of the empty case.
if (empty(stackPtr))
return EMPTY;
// Return the desired item.
return stackPtr->items[stackPtr->top];
}


void print_stack(struct stack* stackPtr) {
printf("\nPrinting the Current stack...");
for(int i=0; i<=stackPtr->top; i++)
printf("%d ", stackPtr->items[i]);
}
/*
* -------------------------------------------------------------------
*
* This marks the start of the functions you must complete
*/
int checkBalance(char exp[])
{
int valid = 1;
struct stack mine;
// Set up the stack and push a couple items, then pop one.
initialize(&mine);
printf("\nChecking balance...\n");
for(int i=0; exp[i]!='\0'; i++)
{
if(exp[i]=='(' || exp[i]=='{' ||exp[i]=='[')
push(&mine, exp[i]);
else if(exp[i]==')')
{
char a = pop(&mine);
if (a=='I' || a !='(')
{
valid =0;
printf("INVALID for )!!!\n");
return valid;
}
//printf("so far valid");
}
else if(exp[i]=='}')
{
char a = pop(&mine);
if (a=='I' || a !='{')
{
valid = 0;
printf("INVALID for }!!!\n"); 
return valid;
}
}
else if(exp[i]==']')
{
char a = pop(&mine);
if (a=='I' || a !='[')
{
valid = 0;
printf("INVALID for ]!!!\n");
return valid;
}
}
}
if (!empty(&mine)) //it means we still have a parenthesis in the stack
{
valid= 0;
printf("INVALID. You have extra!!!\n");
}
if(valid==1)
printf("VALID\n");
return valid;
}

int priority(char ch){
if(ch == '(' || ch == '[' || ch == '{') return 0;
if(ch == '+' || ch == '-') return 1;
if(ch == '*' || ch == '/' || ch == '%') return 2;
if(ch == '^') return 3;
}

int isOperator(char ch){

    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='^')
    return 1;
return 0;
}

char *infixToPostfix(char infix[]){
    struct stack operators;
    initialize(&operators);
    
    int count=0;//keep track of postfix index

    char *postfix=malloc(sizeof(char)*(strlen(infix)+1)*2);
    int len=strlen(infix);
    for(int i=0;i<len;i++){
        if(isdigit(infix[i])){
            //deal with multiple digits
            while(isdigit(infix[i])){
                postfix[count]=infix[i];
                i++;
                count++;
            }
            i--;
            //adding whitespace between numbers
            postfix[count]=' ';
            count++;
        }
        else if(isOperator(infix[i])){
            //if the stack is empty, push the operator
            if(empty(&operators))
                push(&operators,infix[i]);
            else{
                //if the priority is lower or equal,pop the stack into the postfix until it is empty or the priority of the char is higher than the one from the top of the stack
                while(!empty(&operators)&&priority(peek(&operators))>=priority(infix[i])){
                    postfix[count]=pop(&operators);
                    count++;
                    postfix[count]=' ';
                    count++;
                }
                push(&operators,infix[i]); //push current operator onto stack
            }
        }
        else if(infix[i]=='('||infix[i]==')'){
            //if it is an open parentheses, push it to operators
            if(infix[i]=='(')
                push(&operators,infix[i]);
            else{
                //else pop the operators stack into the postfix until it gets to an open parentheses
                while(!empty(&operators)&&peek(&operators)!='('){
                    postfix[count]=pop(&operators);
                    count++;
                    postfix[count]=' ';
                    count++;
                }
                pop(&operators); 
            }
        }
    } //end of iterating through the infix
    
    //pop all the operators left in the stack and add white spaces between them
    while(!empty(&operators)){
        postfix[count]=pop(&operators);
        count++;
        postfix[count]=' ';
        count++;
    }
    
    return postfix;
}

int isParentheses(char ch1){
if(ch1=='('||ch1==')'||ch1=='{'||ch1=='}'||ch1=='['||ch1==']')
    return 1;
return 0;
}