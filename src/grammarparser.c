#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammarparser.h"
#include "stringutils.h"

Node* copyRule(Node* rule) {
	Node *iterator = rule;
	Node *copy = NULL;
	while (iterator != NULL) {
		char* newProd = (char*) malloc(sizeof(char) * (strlen((char*)iterator->data.data)+1));
		//char* newProd = strdup((char*)iterator->data.data);
		strcpy(newProd, (char*) iterator->data.data);
		Data newData;
		if (strcmp(iterator->data.type, "NonTerminal") == 0) {
			newData = (Data) {"NonTerminal", newProd };
		}
		else if (strcmp(iterator->data.type, "Terminal") == 0) {
			newData = (Data) {"Terminal", newProd };
		}
		else {
			newData = (Data) {"Range", newProd };
		}
		push_back(&copy, newData);
		iterator = iterator->next;
	}
	return copy;
}

Node* copyGrammar(Node* grammar) {
	Node *iterator = grammar;
	Node *copy = NULL;
	while (iterator != NULL) {
		Data newData = { "Rule", copyRule((Node*)iterator->data.data)};
		push_back(&copy, newData);
		iterator = iterator->next;
	}
	return copy;
}

Node* newStack() {
	Node* stack = NULL;
	return stack;
}

void addSequence(Node** stack, Node* rule) {
	Node *iterator = rule;
	// shouldn't be the case but just in case
	if (iterator == NULL) return;
	// skip over leading NonTerminal
	Node* newStack = copyRule(iterator->next);
	Node* stackIt = *stack;
	// append items from the current stack to the new stack
	while (stackIt != NULL) {
		// do not add empty strings to the stack
		if (stackIt->data.data != NULL && strlen(stackIt->data.data)!=0 ) {
			push_back(&newStack, stackIt->data);
			stackIt = stackIt->next;
		}
	}
	deleteAll(stack);
	// set the new stack as the current stack
	*stack = newStack;
}

int popIfMatch(Node** stack, char** sequence) {
	Node* iterator = *stack;
	Node* prev = NULL;
	int i = 0;
	// check to see if next item on the stack
	// is a Terminal or Range and if it matches
	// modify the sequence accordingly
	if (iterator != NULL) {
		Data nextSymbol = iterator->data;
		if (nextSymbol.type== "Terminal") {
			char* nextTerminal = nextSymbol.data;
			// check if the next Terminal is a substring of the current sequence
			int len = strlen(nextTerminal);
			if (strncmp(nextTerminal, *sequence, len) == 0) {
				// remove the Terminal from the stack if it matches
					char* temp = substr(*sequence, len, strlen(*sequence));
					free(*sequence);
					*sequence = temp;
					free(pop(stack).data);
				return TRUE;
			}
		}
		// do a range comparison min max
		else if (nextSymbol.type == "Range") {
			char* nextRange = nextSymbol.data;
			char min = nextRange[0];
			char max = nextRange[1];
			if (strlen(*sequence) > 0 && min <= (*sequence)[0] && (*sequence)[0] <= max) {
				char* temp = substr(*sequence, 1, strlen(*sequence));
				free(*sequence);
				*sequence = temp;
				pop(stack);
				return TRUE;
			}
		}
	}
	return FALSE;
}

void deleteStack(Node** stack) {
	while (*stack != NULL) {
		//free(iterator->data.data);
		free(pop(stack).data);
		//iterator = iterator->next;
	}
	//deleteAll(stack);
}

// takes an arbitrary grammar structure and determines if a corresponding string is
// in the language defined by the grammar
int parseStringGrammar(Node* grammar, char* string, int showStack) {
	if (grammar == NULL) return FALSE;
	char *copyOfString = (char*) malloc(sizeof(char)*(strlen(string)+1));
	strcpy(copyOfString, string);

	// starting symbol is the leading non Terminal of the first rule in the grammar
	char* str = ((Node*)(grammar->data.data))->data.data;
	char* startingSymbol = (char*) malloc(sizeof(char)*(strlen(str)+1));
	strcpy(startingSymbol, str);
	Node* stack = NULL;
	push(&stack, (Data) { "NonTerminal", startingSymbol });

	// parse the input string
	int stringInLang = parse(grammar, &stack, &copyOfString, showStack);

	free(copyOfString);
	//clear contents of stack
	 
	Node* itStack = stack;
	while (itStack != NULL) {
		free(itStack->data.data);
		itStack = itStack->next;
	}
	deleteAll(&stack);
	return stringInLang;
}

void printCurrentStack(Node* stack, char* string) {
	printf("Current Input: \"%s\", ", string);
	printf("Stack: [");
	Node* it = stack;
	while (it != NULL) {
		if (it->data.type == "NonTerminal") {
			printf("%s ", (char*) it->data.data);
		}
		else if (it->data.type == "Terminal") {
			printf("%s ", (char*) it->data.data);
		}
		else {
			printf("%s ", (char*) it->data.data);
		}
		it = it->next;
	}
	printf("]\n");
}

// parses a string based on a stack of symbols
int parse(Node* grammar, Node** stack, char** currString, int showStack) {
	printCurrentStack(*stack, *currString);
	// if the current string and stack are empty then the string is in the language
	// if the stack is empty but current string is not then the string is not in the language
	if (isEmpty(*stack)) { 
		*stack = NULL;
		return strlen(*currString) == 0;
	}
	// next stack symbol is NonTerminal
	if ((*stack)->data.type == "NonTerminal") {
		Node *it = grammar;
		// make a copy of the current stack in case backtracking is needed
		Node* copy = copyRule(*stack);
		char *cInput = strdup(*currString);
		while (it != NULL) {
			char* leading = ((Node*)(it->data.data))->data.data;
			// check if the leading NonTerminal (for the Rule) matches the current NonTerminal on the stack
			if (strcmp(leading, (*stack)->data.data) == 0) {
				// remove the current NonTerminal from the stack
				free(pop(stack).data);
				// add the sequence of the rule to the stack
				addSequence(stack, (Node*)(it->data.data));
				// parse the string with the new stack
				int stringInLang = parse(grammar, stack, currString, showStack);
				// if the string is in the language return true
				// and delete the copy of the stack
				if (stringInLang) {
					free(cInput);
					deleteStack(&copy);
					return TRUE;
				}
				// otherwise backtrack to the previous stack
				// and find a new rule that matches the current NonTerminal
				printf("Backtracking: ");
				free(*currString);
				deleteStack(stack);
				*stack = copyRule(copy);
				*currString = strdup(cInput);
				printCurrentStack(*stack, *currString);
			}
			it = it->next;
		}
		deleteStack(&copy);
		free(cInput);
	}
	// if the leading stack symbol is a Terminal or Range
	// match it with the current (unparsed) string
	// to see if an index 0 substring of the string matches the Terminal or Range
	else {
		if (popIfMatch(stack, currString)) {
			// if the string matches the Terminal or Range
			// then parse the string with the new stack
			return parse(grammar, stack, currString, showStack);
		}
	}
	// Current string does not match any rules
	// String is not in the language
	return FALSE;
}
