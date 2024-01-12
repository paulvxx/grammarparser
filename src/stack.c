#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


// add an element to the stack
void push(Node** stack, Data data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = *stack;
	*stack = new_node;
}

// remove an element from the stack
Data* pop(Node** stack) {
	if (isEmpty(*stack)) return NULL;
	Node* temp = *stack;
	Data* data = &(temp->data);
	*stack = temp->next;
	free(temp);
	return data;
}

// get the size of the stack
int size(Node* stack) {
	int size = 0;
	while (stack != NULL) {
		size++;
		stack = stack->next;
	}
	return size;
}

// check if the stack is empty
int isEmpty(Node* stack) {
	return stack == NULL;
}

void printStringStack(Node* stack) {
	while (stack != NULL) {
		if (stack->data.type=="string") {
			printf("%s\n", (char*)stack->data.data);
		}
		if (stack->data.type == "terminal") {
			printf("%s\n", (char*)stack->data.data);
		}
		if (stack->data.type == "nonTerminal") {
			printf("%s\n", (char*)stack->data.data);
		}
		stack = stack->next;
	}
}