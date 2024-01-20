#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "stringutils.h"

#ifndef GRAMMAR_PARSER_H
#define GRAMMAR_PARSER_H

// makes a deep copy of a grammar Rule
Node* copyRule(Node* rule);

// makes a deep copy of the grammar list
Node* copyGrammar(Node* grammar);

// creates a new stack used to parse the grammar
Node* newStack();

// adds a new sequence to the current stack
void addSequence(Node** stack, Node* rule);

// pops the first element of the stack if it is a substring of the current sequence
// returns true if the pop was successful
int popIfMatch(Node** stack, char** sequence);

// deletes the current stack
void deleteStack(Node** stack);

// takes an arbitrary grammar structure and determines if a corresponding string is
// in the language defined by the grammar
int parseStringGrammar(Node* grammar, char* string);

// prints the current stack
void printCurrentStack(Node* stack, char* string);

// parses a string based on a stack of symbols
int parse(Node* grammar, Node** stack, char** currString);

#endif GRAMMAR_PARSER_H