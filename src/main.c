#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "grammarparser.h"
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
	printf("------------------\n");
	while (iterator != NULL) {
		printf("Type = % s  Data : % s\n", (char*)iterator->data.type, (char*)iterator->data.data);
		iterator = iterator->next;
	}
	printf("------------------\n");
}

void printGrammar(Node* grammar) {
	Node *iterator = grammar;
	while (iterator != NULL) {
		printf("%s:\n", (char*)iterator->data.type);
		printRule((Node*) iterator->data.data);
		iterator = iterator->next;
	}
	printf("\nDONE------------------DONE\n");
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

	//printGrammar(grammar);
	// test the copy function:
	Node* copy = copyGrammar(grammar);

	// Free All memory
	deleteGrammar(&grammar);
	printGrammar(copy);
	//deleteGrammar(&copy);

	Node* stack = NULL;
	push(&stack, (Data) { "Range", "tz" });
	push_back(&stack, (Data) {"Terminal", "acd"});
	push_back(&stack, (Data) { "NonTerminal", "B" });
	push_back(&stack, (Data) {"NonTerminal", "C" });
	push_back(&stack, (Data) {"Terminal", "ee"});


	//addSequence(&stack, (Node*) copy->data.data);
	//addSequence(&stack, (Node*) copy->data.data);
	//addSequence(&stack, (Node*) (copy->next)->data.data);
	//addSequence(&stack, (Node*) (copy->next)->data.data);
	//addSequence(&stack, (Node*) (copy->next->next)->data.data);
	//printRule(stack);
	//printRule(stack);

	push_back(&stack, (Data) { "Terminal", "fgh" });

	char* c = malloc(sizeof(char) * (strlen("xddaBdacC")+1));
	strcpy(c, "xddaBdacC");
	//printf("Before: %s\n", c);
	popIfMatch(&stack, &c);
	//printf("After: %s\n", c);
	free(c);

	Node* dcopy = copyRule(stack);

	deleteAll(&stack);
	//printCurrentStack(dcopy, "dddddd");
	//Node* gt = NULL;
	//push_back(&gt, (Data) {"S", NULL});
	//Node *itStack = stack;
	//while (itStack != NULL) {
	//	free(itStack->data.data);
	//	itStack = itStack->next;
	//}
	//printRule(dcopy);

	//printRule(stack);
	//Node* gt = NULL;
	//push_back(&gt, (Data) {"S", NULL});
	// 
	Node *itStack = dcopy;
	while (itStack != NULL) {
		free(itStack->data.data);
		itStack = itStack->next;
	}

	deleteAll(&dcopy);


	char* ipStr = "aac";
	char *input = malloc(sizeof(char) * (strlen(ipStr)+1));
	strcpy(input, ipStr);
	int inLang = parseStringGrammar(copy, input);
	//int inLang = TRUE;
	if (inLang) {
		printf("String is in the language\n");
	}
	else {
		printf("String is not in the language\n");
	}
	free(input);
	deleteGrammar(&copy);
	//free(gt);
	//free(grammar);
	free(toParse);
	return 0;
}
