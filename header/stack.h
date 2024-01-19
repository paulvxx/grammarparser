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

// get data at specified index
Data get(Node* stack, int index);

// remove an element from the stack
Data pop(Node** stack);

// may also serve as a queue in some cases

// adds an element to the back of the stack
void push_back(Node** stack, Data data);

// removes an element from the back of the stack
Data pop_back(Node** stack);

void deleteAll(Node** stack);

// get the size of the stack
int size(Node* stack);

// check if the stack is empty
int isEmpty(Node * stack);
