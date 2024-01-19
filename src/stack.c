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
Data get(Node* stack, int index) {
	if (isEmpty(stack)) return (Data) {NULL, NULL};
	Node* n = stack;
	int i = 0;
	while (i < index && n != NULL) {
		n = n->next;
		i++;
	}
	if (n == NULL) return (Data) {NULL, NULL};
	//printf("made it\n");
	return n->data;
}


// remove an element from the stack
Data pop(Node** stack) {
	if (isEmpty(*stack)) return (Data) {NULL, NULL};
	Node* temp = *stack;
	Data data = temp->data;
	*stack = temp->next;
	free(temp);
	return data;
}


// could serve as a queue in some cases
// adds an element to the back of the stack
void push_back(Node** stack, Data data) {
	//if (*stack == NULL) printf("Yay\n");

	if (isEmpty(*stack)) {
		//printf("Yay\n");
		push(stack, data);
		return;
	}
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	Node *n = *stack;
	//printf("done %d\n", (n->next)==NULL);
	while (n->next != NULL) {
		n = n->next;
	}
	n->next = new_node;
}  

// could serve as a queue in some cases
// removes an element from the back of the stack
Data pop_back(Node** stack) {
	if (isEmpty(*stack)) return (Data){NULL, NULL};

	// Only one node in the list
	if ((*stack)->next == NULL) return pop(stack);

	Node* n = *stack;
	// Traverse the list until the second-to-last node
	while (n->next->next != NULL) {
		n = n->next;
	}

	Node* last = n->next;
	Data data = last->data;
	free(last);
	n->next = NULL;  // Set the next pointer of the second-to-last node to NULL
	return data;
}

// deletes all elements from the list
void deleteAll(Node** stack) {
	while (!isEmpty(*stack)) {
		pop(stack);
	}
}

// get the size of the stack
int size(Node* stack) {
	int size = 0;
	Node* n = stack;
	while (n != NULL) {
		size++;
		n = n->next;
	}
	return size;
}

// check if the stack is empty
int isEmpty(Node* stack) {
	return stack == NULL;
}

