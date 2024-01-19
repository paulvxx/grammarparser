#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "grammarformatparser.h"


void deleteGrammar(Node **grammar) {
	Node* iterator = *grammar;
	while (iterator != NULL) {
		Node* list = (Node*)iterator->data.data;
		//printf("New LIST DELETING:\n");
		while (list != NULL) {
			free(list->data.data);
			list = list->next;
		}
		list = (Node*)iterator->data.data;
		deleteAll(&list);
		iterator = iterator->next;
	}
	deleteAll(grammar);
}

void printRule(Node* rule) {
	Node *iterator = rule;
	while (iterator != NULL) {
		printf("Type=%s  Data: %s\n", (char*)iterator->data.type, (char*)iterator->data.data);
		iterator = iterator->next;
	}
}

void printGrammar(Node* grammar) {
	Node *iterator = grammar;
	while (iterator != NULL) {
		printf("%s:\n", (char*)iterator->data.type);
		printRule((Node*) iterator->data.data);
		iterator = iterator->next;
	}
}

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char* toParse = parseFile("test2.txt");
	int error = TRUE;
	int pos = 0;
	Node* grammar = NULL;

	if (parseGrammar(toParse, &pos, &error, &grammar)) {
		printf("Grammar is valid\n");
	}
	else {
		printf("Grammar is invalid\n");
	}

	printGrammar(grammar);

	// Free All memory
	deleteGrammar(&grammar);

	//Node* gt = NULL;
	//push_back(&gt, (Data) {"S", NULL});

	//free(gt);
	//free(grammar);
	free(toParse);
	return 0;
}
