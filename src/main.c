#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <crtdbg.h>
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
	if (iterator != NULL) {
		printf("<%s> --> ", (char*)iterator->data.data);
		iterator = iterator->next;
	}
	while (iterator != NULL) {
		if (strcmp((char*)iterator->data.type, "NonTerminal") == 0) {
			printf("<%s> ", (char*)iterator->data.data);
		}
		else {
			printf("\"%s\" ", (char*)iterator->data.data);
		}
		iterator = iterator->next;
	}
}

void printGrammar(Node* grammar) {
	Node *iterator = grammar;
	printf("Grammar:\n");
	printf("------------------");
	while (iterator != NULL) {
		printf("\n");
		printRule((Node*) iterator->data.data);
		iterator = iterator->next;
	}
	printf("\n------------------\n");
}


void printHelpMessage() {
	printf("A program to check if a string is in the language of an arbitrary grammar\n");
	printf("Usage: ./grammarparser (Optional: -t) <grammar file> (Optional: -s) <string to parse> (Optional: -s) <string to parse> ...\n");
	printf("Optional: <string to parse>");
	printf("Flags:\n");
	printf("-t: Print the parsed text (Grammar). Occurs right before filename argument");
	printf("-s: Print the stack trace for the given derivation of the string. Occurs right before each input string on the command line\n");
	printf("To print this message again, run the program with no arguments\n");
	printf("Syntax for grammar file:\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("<Grammar> ::= <NonTerminalInit> '\\n' <ListOfRules>\n");
	printf("<NonTerminalInit> ::= '[' <ListOfNonTerminals> ']'\n");
	printf("<ListOfNonTerminals> ::= <NonTerminal> ',' <ListOfNonTerminals> | <NonTerminal>\n");
	printf("<NonTerminal> ::= {'A' - 'Z'} {'A' - 'Z' | 'a' - 'z'}*\n");
	printf("<ListOfRules> ::= <Rule> <ListOfRules> | <Rule>\n");
	printf("<Rule> ::= <NonTerminal> '::=' <ListOfProductions> ';' '\\n'\n");
	printf("<ListOfProductions> ::= <ProductionSequence> '|' <ListOfProductions> | <ProductionSequence>\n");
	printf("<ProductionSequence> ::= <Production> <ProductionSequence> | <CharRange> <ProductionSequence> | <Production> | <CharRange>\n");
	printf("<Production> ::= <Terminal> <Production> | <NonTerminal> <Production> | <Terminal> | <NonTerminal>\n");
	printf("<Terminal> ::= <String>\n");
	printf("<String> ::= '\"' # <StringTokenList> # '\"'\n");
	printf("<StringTokenList> ::= # <StringToken> # <StringTokenList> # | ''\n");
	printf("<StringToken> ::= {'A' - 'Z' | 'a' - 'z' | '0' - '9' | '!' | '@' | '#' | '$' | '%' | '^' | '&' | '*' |\n");
	printf(" '(' | ')' | '_' | '-' | '+' | '=' | '{' | '}' | '[' | ']' | '|' | ':' |\n");
	printf(" ';' | '<' | '>' | ',' | '.' | '?' | '/' | '`' | '~' |\n");
	printf(" '\\a' | '\\b' | '\\f' | '\\n' | '\\r' | '\\t' | '\\v' | '\\?' | '\\\\' | '\\'' | '\\\"' }*\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Note: All non-terminal sybmols must be initialized in the first line of the grammar file\n");
	printf("Note: Comments and spaces are generally ignored\n");
	printf("Comments may occur after a rule equality token '::=', a '|' symbol, after the list of non-terminals, or after a rule i.e. the ';' end symbol\n");
	printf("Comments are denoted by a '!!' and end with a newline character\n");
	printf("Spaces are ignored except in the case of a string, where they are treated as a character\n\n");
	printf("The prgram will print whether or not each string is in the language of the grammar\n");
	printf("The algorithm used is a recursive descent parser along with a backtracking algorithm,\n");
	printf("allowing for the ability to parse a variety of languages\n");
	printf("The grammar file must be in the format specified above\n");
	printf("There are limitations, however\n");
	printf("Due to the nature of the algorithm, the grammar cannot contain a left recursion cycle\n");
	printf("This is not yet checked, so it is up to the user to ensure that the grammar does not contain a left recursion cycle\n");
}

int main(int argc, char* argv[]) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// print a help message if no command line arguments are given
	if (argc == 1) {
		printHelpMessage();
		return 0;
	}

	int argPos = 1;
	// check for flags
	int text = (strcmp(argv[1], "-t") == 0);
	// command line arguments are invalid
	// missing filename
	if (text) {
		if (argc == 2) {
			ERROR("Missing filename\n");
			ERROR("Run this program without arguments to see the help message\n");
			return 1;
		}
		else argPos++;
	}

	// first command line argument is the grammar file
	char* toParse = parseFile(argv[argPos]);
	int error = TRUE;
	int pos = 0;
	Node* grammar = NULL;
	argPos++;

	// parse the grammar file to obtain a grammar
	if (parseGrammar(toParse, &pos, &error, &grammar)) {
		printf("Grammar is valid\n");
	}
	else {
		printf("Grammar is invalid\n");
		free(toParse);
		deleteGrammar(&grammar);
		return 0;
	}
	if (text) {
		printGrammar(grammar);
		printf("\n");
	}

	// rest of the command line arguments are test strings to parse
	while (argPos < argc) {
		int showStack = (strcmp(argv[argPos], "-s") == 0);
		if (showStack) {
			printf("\n");
			argPos++;
		}
		char* input = malloc(sizeof(char) * (strlen(argv[argPos]) + 1));
		strcpy(input, argv[argPos]);
		int inLang = parseStringGrammar(grammar, input, showStack);
		if (inLang) {
			printf("Input %s: String is in the language\n", input);
		}
		else {
			printf("Input %s: String is not in the language\n", input);
		}
		free(input);
		argPos++;
	}
	free(toParse);
	deleteGrammar(&grammar);
	return 0;
}
