#include <stdio.h>
#include <stdarg.h>

#define TRUE 1
#define FALSE 0
#include <stack.h>
#include <string.h>
#include "stack.h"
#include "grammarformatparser.h"
#include "charsetlist.h"

// Adds a character to the current set (as a stack) 
void pushToCharSet(Node** charset, char* c) {
	Data data;
	data.type = "character";
	data.data = *c;
	push(charset, data);
}

// Adds a character to the current set of CharSets (as a stack)
void pushToCharSetList(Node** charsetList, Node** charset, int repeats) {
	Data data;
	if (repeats) {
		data.type = "repeated";
	}
	else {
		data.type = "charset";
	}
	data.data = charset;
	push(charsetList, data);
};

// Prints a character set
void printCharSet(Node* charsetList, int repeated) {
Node* current = charsetList;
	printf("{");
	while (current != NULL) {
		if (strcmp(current->data.type, "character") == 0) {
			printf("\'%c\'", *(char*)current->data.data);
			if (current->next != NULL) printf(", ");
		}
		current = current->next;
	}
	printf("}");
	if (repeated) {
		printf("*");
	}
}

// Prints a character set list
void printCharSetList(Node* charsetList) {
	Node* current = charsetList;
	while (current != NULL) {

		if (strcmp(current->data.type, "repeated") == 0) {
			printf("repeated ");
		}
		else if (strcmp(current->data.type, "charset") == 0) {
			printf("charset ");
		}
		current = current->next;
	}
	printf("\n");
}