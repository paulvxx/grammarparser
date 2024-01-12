#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for Data element
typedef struct Data {
	char* type;
	void* data;
} Data;

// structure for a node in a linked list (stack)
typedef struct Node {
	Data data;
	struct Node* next;
} Node;

// structure for a stack

// add an element to the stack
void push(Node** stack, Data data);

// remove an element from the stack
Data* pop(Node** stack);

// get the size of the stack
int size(Node* stack);

// check if the stack is empty
int isEmpty(Node * stack);

// print the stack
void printStack(Node* stack);