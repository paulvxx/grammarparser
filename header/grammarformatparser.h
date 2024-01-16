#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// used to print syntax errors to stderr
int grammarError(char* msg, int *pos, int *errorFlag);

// parses a file and returns a string containing the contents
char* parseFile(char* filename);

// parses a string containing a grammar and returns true if the grammar 
// has valid syntax
//<Grammar> ::= <NonTerminalInit> '\n' <ListOfRules>
int parseGrammar(char* str, int* pos, int* errorFlag);

//<NonTerminalInit> ::= '[' <ListOfNonTerminals> ']'
int parseNonTerminalInit(char* str, int* pos, int* errorFlag);

//<ListOfNonTerminals> ::= <NonTerminal> ',' <ListOfNonTerminals> | <NonTerminal>
int parseListOfNonTerminals(char* str, int* pos, int* errorFlag);

//<NonTerminal> ::= {'A' - 'Z'} {'A' - 'Z' | 'a' - 'z'}*
int parseNonTerminal(char* str, int* pos);

//<ListOfRules> ::= <Rule> <ListOfRules> | <Rule>
int parseListOfRules(char* str, int* pos, int* errorFlag);

//<Rule> ::= <NonTerminal> '::=' <ListOfProductions> ';' '\n'
int parseRule(char* str, int* pos, int* errorFlag);

//<ListOfProductions> ::= <ProductionSequence> '|' <ListOfProductions> | <ProductionSequence>
int parseListOfProductions(char* str, int* pos, int* errorFlag);

//<ProductionSequence> ::= <Production> | <CharSetList>
int parseProductionSequence(char* str, int* pos, int* errorFlag);

//<Production> ::= <Terminal> <Production> | <NonTerminal> <Production> <Terminal> | <NonTerminal>
int parseProduction(char* str, int* pos);

//<Terminal> ::= <String>
int parseTerminal(char* str, int* pos);

//<String> ::= '\"' # <StringTokenList> # '\"'
int parseString(char* str, int* pos);

//<StringTokenList> ::= # <StringToken> # <StringTokenList> # | ''
int parseStringTokenList(char* str, int* pos);

//<StringToken> ::= {'A' - 'Z' | 'a' - 'z' | '0' - '9' | ' ' | '!' | '@' | '#' | '$' | '%' | '^' | '&' | '*' |
// '(' | ')' | '_' | '-' | '+' | '=' | '{' | '}' | '[' | ']' | '|' | ':' |
// ';' | '<' | '>' | ',' | '.' | '?' | '/' | '`' | '~' |
// '\a' | '\b' | '\f' | '\n' | '\r' | '\t' | '\v' | '\?' | '\\' | '\'' | '\"' }*
int parseStringToken(char* str, int* pos);

//<CharSetList> ::= <CharSet> <CharSetList> | <CharSet>
int parseCharSetList(char* str, int* pos, int* errorFlag);

//<CharSet> ::= '{' <CharList> '}' | '{' <CharList> '}*'
int parseCharSet(char* str, int* pos, int* errorFlag);

//<CharList> ::= '\'' # <StringToken> # '\'' ',' <CharList> | '(' <CharRange> ')' <CharList> | <StringToken> | '(' <CharRange> ')'
int parseCharList(char* str, int* pos, int* errorFlag);

//<CharRange> ::= '\'' # <StringToken> # '\'' '...' '\'' # <StringToken> # '\''
int parseCharRange(char* str, int* pos, int* errorFlag);

// parses a comment
void parseComment(char* str, int* pos);

// parses whitespace and comments together
void parseWhiteSpaceAndComments(char* str, int* pos);

// parses whitespace
// newlines = 1 if newlines are allowed, 0 if not
void parseWhiteSpace(char* str, int* pos, int newlines);

// parses a character
int eat(char* str, int* pos, char c);

// parses a string
int eatString(char* str, int* pos, char* s);

// looks ahead for a character
int peek(char* str, int* pos, char c);
