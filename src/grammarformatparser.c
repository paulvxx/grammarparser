#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammarformatparser.h"


// (Note: White space is generally ignored, a '#' symbol denotes no whitespace is allowed)
// (Note: '' deontes an empty string)
// EXPECTED FORMAT:
//<GrammarFile> ::= <ListOfNonTerminals> '\n' <ListOfRules>
//<ListOfNonTerminals> ::= '[' <ListOfNonTerminals> ']'
//<ListOfNonTerminals> ::= <NonTerminal> ',' <ListOfNonTerminals> | <NonTerminal>
//<NonTerminal> ::= {'A' - 'Z'} {'A' - 'Z' | 'a' - 'z'}*
//<ListOfRules> ::= <Rule> <ListOfRules> | <Rule>
//<Rule> ::= <NonTerminal> '::=' <ListOfProductions> ';' '\n'
//<ListOfProductions> ::= <Production> '|' <ListOfProductions> | <Production>
//<Production> ::= <Terminal> <Production> | <NonTerminal> <Production> | <CharSet> <Production> | <Terminal> | <NonTerminal> | <CharSet>
//<Terminal> ::= '\"' # <String> # '\"'
// <String> ::= # <Char> # <String> # | ''
//<Char> ::= {'A'-'Z' | 'a'-'z' | '0'-'9' | ' ' | '!' | '@' | '#' | '$' | '%' | '^' | '&' | '*' | 
// '(' | ')' | '_' | '-' | '+' | '=' | '{' | '}' | '[' | ']' | '|' | ':' | 
// ';' | '<' | '>' | ',' | '.' | '?' | '/' | '`' | '~' |  
// '\a' | '\b' | '\f' | '\n' | '\r' | '\t' | '\v' | '\?' | '\\' | '\'' | '\"' }*
//<CharSet> ::= '{' <CharList> '}' | '{' <CharList> '}*'
//<CharList> ::= '\'' # <StringToken> # '\'' <CharList> | <Char>

// An Example Grammar:
// [A, B, C]
// A ::= "ab" | "c" B | {'!', '@'}*;
// B ::= "cca" B | {'d'}* C | "c";
// C ::= "c" | "d" | "e" | "f" | "g" | "h" A;



char* parseFile(char* filename) {
    FILE* fp;
    char lineBuffer[1024]; // Buffer for each line
    size_t capacity = 1024;
    char* result = malloc(capacity);
    if (result == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(lineBuffer, sizeof(lineBuffer), fp) != NULL) {
        size_t newLength = strlen(result) + strlen(lineBuffer) + 1;
        if (newLength > capacity) {
            capacity = newLength;
            char* temp = realloc(result, capacity);
            if (temp == NULL) {
                free(result);
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
            result = temp;
        }
        strcat(result, lineBuffer);
    }

    fclose(fp);
    return result;
}


