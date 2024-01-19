#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammarformatparser.h"
#include "error.h"


// (Note: White space is generally ignored, a '#' symbol denotes no whitespace is allowed)
// (Note: '' deontes an empty string)
// (Note: Comments are allowed and start with two '!!' marks, and end with a newline character)
// Comments may occur after a rule list, the '::=' indicator or the '|' symbol, after a ';' symbol, before the list of rules (before and after the
// initializer list of Non-Terminals).
// EXPECTED FORMAT:
//<Grammar> ::= <NonTerminalInit> '\n' <ListOfRules>
//<NonTerminalInit> ::= '[' <ListOfNonTerminals> ']' 
//<ListOfNonTerminals> ::= <NonTerminal> ',' <ListOfNonTerminals> | <NonTerminal>
//<ListOfNonTerminals> ::= '[' <ListOfNonTerminals> ']'
//<ListOfNonTerminals> ::= <NonTerminal> ',' <ListOfNonTerminals> | <NonTerminal>
//<NonTerminal> ::= {'A' - 'Z'} {'A' - 'Z' | 'a' - 'z'}*
//<ListOfRules> ::= <Rule> <ListOfRules> | <Rule>
//<Rule> ::= <NonTerminal> '::=' <ListOfProductions> ';' '\n'
//<ListOfProductions> ::= <ProductionSequence> '|' <ListOfProductions> | <ProductionSequence>
//<ProductionSequence> ::= <Production> | <CharSetList>
//<Production> ::= <Terminal> <Production> | <NonTerminal> <Production> | <Terminal> | <NonTerminal>
//<Terminal> ::= <String>
//<String> ::= '\"' # <StringTokenList> # '\"'
//<StringTokenList> ::= # <StringToken> # <StringTokenList> # | ''
//<StringToken> ::= {'A'-'Z' | 'a'-'z' | '0'-'9' | ' ' | '!' | '@' | '#' | '$' | '%' | '^' | '&' | '*' | 
// '(' | ')' | '_' | '-' | '+' | '=' | '{' | '}' | '[' | ']' | '|' | ':' | 
// ';' | '<' | '>' | ',' | '.' | '?' | '/' | '`' | '~' |  
// '\a' | '\b' | '\f' | '\n' | '\r' | '\t' | '\v' | '\?' | '\\' | '\'' | '\"' }*
//<CharSetList> ::= <CharSet> <CharSetList> | <CharSet>
//<CharSet> ::= '{' <CharList> '}' | '{' <CharList> '}*'
//<CharList> ::= '\'' # <StringToken> # '\'' ',' <CharList> | '(' <CharRange> ')' <CharList> | <StringToken> | '(' <CharRange> ')'
//<CharRange> ::= '\'' # <StringToken> # '\'' '...' '\'' # <StringToken> # '\''
// 
//
// An Example Grammar:
// [A, B, C]
// A ::= "ab" | "c" B | {'!', '@'}*;
// B ::= "cca" B | {'d'}* C | "c";
// C ::= "c" | "d" | "e" | "f" | "g" | "h" A;

// This C file is used to parse the grammar format and rules for the grammar
// Non Terminal symbols must be declared at the top of the file in a list
// Subsequent rules for Non Terminal symbols must be listed below using the above syntax
// The grammar format is parsed using a recursive descent parser
// Important data about the grammar is stored in a stack of Nodes
// The stack is used to store the Non Terminal symbols and their rules
// It is the callers responsibility to allocate (initial memory) and free the memory for the stack


int grammarError(char* msg, int *pos, int *errorFlag) {
    if (*errorFlag) {
        ERROR("%s, pos=%d\n", msg, *pos);
        // Set the error flag to false to stop printing errors
        *errorFlag = FALSE;
    }
    return FALSE;
}

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


// <Grammar> ::= <ListOfNonTerminals> '\n' <ListOfRules>
parseGrammar(char* str, int *pos, int* errorFlag, Node** grammar) {
    //parseWhiteSpace(str, pos, TRUE);
    parseWhiteSpaceAndComments(str, pos);
    
    // The grammar node is meant to collect relevant information about the grammar
    // The first element should be a temporary list of all the Non Terminals in order
    // to check that all rules will start with the initialized Non Terminals

    // After parsing all rules, the first element should be deleted
    // For each rule, grammar should contain a node with data, the data containing 
    // a list of the first Non Terminal and its rules
    // an '|' delimiter treats the rules as two separte rules, and thus two separate nodes
    // e.g. if the rule was A ::= "ab" | "c" B then the corresponding nodes would contain
    // first Node:
    // first element would contain data type "Non Terminal" and data value "A"
    // second element would contain data type "Terminal" and data value "ab"
    // second Node:
    // first element would contain data type "Non Terminal" and data value "A"
	// second element would contain data type "Terminal" and data value "c"
    // third element would contain data type "Non Terminal" and data value "B"



    // IGNORE THESE COMMENTS
    // initialize a temporary stack to store all Non Terminals
    
    Node* nonTerminalsInit = NULL;
    Data ntTemp = {NULL, nonTerminalsInit};
    push_back(grammar, ntTemp);   

    //Node* cnt = (get(*grammar, 0).data);
    //printf("%d\n", size(*grammar));
    //Node* cnt2 = (get(grammar, 1).data);
    //printf("IS : %d\n", ((cnt2 == NULL)));
    //printf("sSSS %d\n", cnt == nonTerminalsInit);
    //printf("sSSS %d\n", (*cnt == *nonTerminalsInit));

    //if (cnt != NULL && cnt->data.data != NULL) {
    //    printf("String: %s\n", (char*)(cnt->data.data));  // Assuming cnt->data is a Node* whose data is a string
    //}
    //else {
    //    printf("Error: Null pointer encountered\n");
    //}

    if (!parseNonTerminalInit(str, pos, errorFlag, grammar)) return FALSE;
    parseWhiteSpace(str, pos, FALSE);
    if ((*pos) + 1 < strlen(str) && str[*pos] == '!' && str[(*pos) + 1] == '!') {
        parseComment(str, pos);
    }
    else if (!eat(str, pos, '\n')) return FALSE;
    if (!parseListOfRules(str, pos, errorFlag, grammar)) return FALSE;



    // IGNORE THESE COMMENTS
    // free the temporary stack
    
    printf("Strings:   ");
    nonTerminalsInit = ((Node*)(*grammar)->data.data);
    //printf("E %d\n", size(nonTerminalsInit));
    while (!isEmpty(nonTerminalsInit)) {
        printf("%s  ", (char*)nonTerminalsInit->data.data);
        free(nonTerminalsInit->data.data);
		pop(&nonTerminalsInit);
	}
    printf("\n");
    pop(grammar);
    return TRUE;
}

int parseNonTerminalInit(char* str, int* pos, int* errorFlag, Node** grammar) {
	if (!eat(str, pos, '[')) return grammarError("Missing \'[\'", pos, errorFlag);
	if (!parseListOfNonTerminals(str, pos, errorFlag, grammar)) return FALSE;
	if (!eat(str, pos, ']')) return grammarError("Missing \']\'", pos, errorFlag);
	return TRUE;
}

int parseListOfNonTerminals(char* str, int* pos, int* errorFlag, Node** grammar) {
    parseWhiteSpace(str, pos, TRUE);
    int oldPos = *pos;
    if (!parseNonTerminal(str, pos)) return FALSE;
    char* nt = substr(str, oldPos, *pos);

    // dereferncing nonTerminalsInit List
    Node* ntList = (Node*) get(*grammar, 0).data;
    printf("s %d\n", size(ntList));
    push_back(&ntList, (Data) {NULL, nt});
    printf("String added: %s\n", nt);
    (*grammar)->data = (Data) {NULL, ntList};

    parseWhiteSpace(str, pos, TRUE);
    if (eat(str, pos, ',')) {
        if (!parseListOfNonTerminals(str, pos, errorFlag, grammar)) return FALSE;
    }
    return TRUE;
}

int parseListOfRules(char* str, int* pos, int* errorFlag, Node* grammar) {
    parseWhiteSpaceAndComments(str, pos);
	if (!parseRule(str, pos, errorFlag, grammar)) return FALSE;
    parseWhiteSpaceAndComments(str, pos);
	if ((*pos) < strlen(str)) {
		if (!parseListOfRules(str, pos, errorFlag, grammar)) return FALSE;
	}
	return TRUE;
}

int parseRule(char* str, int* pos, int* errorFlag, Node* grammar) {
	if (!parseNonTerminal(str, pos)) return grammarError("Missing Starting Symbol for Rule", pos, errorFlag);
    parseWhiteSpace(str, pos, FALSE);
	if (!eat(str, pos, ':')) return grammarError("Missing \':\'", pos, errorFlag);
	if (!eat(str, pos, ':')) return grammarError("Missing \':\'", pos, errorFlag);
	if (!eat(str, pos, '=')) return grammarError("Missing \'=\'", pos, errorFlag);
	if (!parseListOfProductions(str, pos, errorFlag, grammar)) return FALSE;
	if (!eat(str, pos, ';')) return grammarError("Missing \';\'", pos, errorFlag);
    parseWhiteSpace(str, pos, FALSE);
    if ((*pos) + 1 < strlen(str) && str[*pos] == '!' && str[(*pos) + 1] == '!') {
        parseComment(str, pos);
    }
	else if (!eat(str, pos, '\n')) return grammarError("Missing newline character", pos, errorFlag);
	return TRUE;
}

int parseListOfProductions(char* str, int* pos, int* errorFlag, Node* grammar) {
    parseWhiteSpaceAndComments(str, pos);
    if (!parseProductionSequence(str, pos, errorFlag, grammar)) return FALSE;
    parseWhiteSpace(str, pos, TRUE);
    // logical OR (choice)
	if (!eat(str, pos, '|')) return TRUE;
	if (!parseListOfProductions(str, pos, errorFlag, grammar)) return grammarError("Production Rule after \'|\' cannot be blank", pos, errorFlag);
	return TRUE;
}

int parseProductionSequence(char* str, int* pos, int *errorFlag, Node* grammar) {
	parseWhiteSpace(str, pos, TRUE);
    if (parseCharSetList(str, pos, errorFlag, grammar));
	else if (!parseProduction(str, pos, grammar)) return FALSE;
	parseWhiteSpace(str, pos, TRUE);
	// logical AND (sequence)
	if (!parseProductionSequence(str, pos, errorFlag, grammar)) return TRUE;
	return TRUE;
}

int parseProduction (char* str, int* pos, Node* grammar) {
    // check which type of symbol/production it is
    if (peek(str, pos, '\"')) {
		if (!parseTerminal(str, pos)) return FALSE;
	}
    else {
        if (!parseNonTerminal(str, pos)) return FALSE;
	}
    return TRUE;
}

int parseNonTerminal(char* str, int* pos) {
    if (*pos >= strlen(str)) return FALSE;
    // Uppercase letter
    if (('Z' - str[*pos]) < 0 || (str[*pos] - 'A') < 0) return FALSE;
    eat(str, pos, str[*pos]);
    // keep scanning for letters
    while ( ((*pos) < strlen(str)) && (('Z' - str[*pos]) >= 0 && (str[*pos] - 'A') >= 0) || (('z' - str[*pos]) >= 0 && (str[*pos] - 'a') >= 0)) {
        eat(str, pos, str[*pos]);
    }
	return TRUE;
}

int parseTerminal(char* str, int* pos) {
    return parseString(str, pos);
}

int parseString(char* str, int* pos) {
    if (!eat(str, pos, '\"')) return FALSE;
    eat(str, pos, '\"');
    if (peek(str, pos, '\"')) return eat(str, pos, '\"'); //TRUE
	if (!parseStringTokenList(str, pos)) return FALSE;
    if (!eat(str, pos, '\"')) return FALSE;

	return TRUE;
}


int parseStringTokenList(char* str, int* pos) {
	//int startPos = *pos;
	while (parseStringToken(str, pos));
	//*pos = startPos;
	return TRUE;
}

int parseStringToken(char* str, int* pos) {
    int startPos = *pos;
    if (peek(str, pos, '\'') || peek(str, pos, '\"')) {
        return FALSE;
	}
    else if (peek(str, pos, '\\')) {
        eat(str, pos, '\\');
        if (peek(str, pos, 'a') || peek(str, pos, 'b') || peek(str, pos, 'f') || peek(str, pos, 'n') 
           || peek(str, pos, 'r') || peek(str, pos, 't') || peek(str, pos, 'v') || peek(str, pos, '?')
            || peek(str, pos, '\\') || peek(str, pos, '\'') || peek(str, pos, '\"')) {
            return eat(str, pos, str[(*pos)]);
        }
        else return FALSE;
    }
    else {
        (*pos)++;
    }
    return TRUE;
}

int parseCharSetList(char* str, int* pos, int* errorFlag, Node* grammar) {
	parseWhiteSpace(str, pos, TRUE);
    if (!peek(str, pos, '{')) return FALSE;
	if (!parseCharSet(str, pos, errorFlag, grammar)) return FALSE;
	parseWhiteSpace(str, pos, TRUE);
    if (peek(str, pos, '{')) {
        if (!parseCharSetList(str, pos, errorFlag, grammar)) return FALSE;
    }
	return TRUE;
}

int parseCharSet(char* str, int* pos, int *errorFlag, Node* grammar) {
	if (!eat(str, pos, '{')) return grammarError("Missing \'{\'", pos, errorFlag);
	if (!parseCharList(str, pos, errorFlag, grammar)) return FALSE;
	if (!eat(str, pos, '}')) return grammarError("Missing \'}\'", pos, errorFlag);
	if (eat(str, pos, '*')) return TRUE;
	return TRUE;
}

int parseCharList(char* str, int* pos, int* errorFlag, Node* grammar) {
    parseWhiteSpace(str, pos, TRUE);
    if (peek(str, pos, '(')) {
		if (!eat(str, pos, '(')) return grammarError("Missing \'(\', Expected Character Range", pos, errorFlag);
        parseWhiteSpace(str, pos, FALSE);
		if (!parseCharRange(str, pos, errorFlag)) return FALSE;
        parseWhiteSpace(str, pos, FALSE);
		if (!eat(str, pos, ')')) return grammarError("Missing \')\', Expected Character Range", pos, errorFlag);
	}
	else {
		if (!eat(str, pos, '\'')) return grammarError("Missing \' quotation mark, Expected Character", pos, errorFlag);
		if (!parseStringToken(str, pos)) return FALSE;
		if (!eat(str, pos, '\'')) return grammarError("Missing \' quotation mark, Expected Character", pos, errorFlag);
	}
    parseWhiteSpace(str, pos, TRUE);
    if (eat(str, pos, ',')) {
        if (!parseCharList(str, pos, errorFlag, grammar)) return FALSE;
    }
    return TRUE;
}

int parseCharRange(char *str, int* pos, int* errorFlag) {
	if (!eat(str, pos, '\'')) return grammarError("Missing \' quotation mark, Expected Character", pos, errorFlag);
	if (!parseStringToken(str, pos)) return FALSE;
	if (!eat(str, pos, '\'')) return grammarError("Missing \' quotation mark, Expected Character", pos, errorFlag);
    parseWhiteSpace(str, pos, FALSE);
	if (!eat(str, pos, '.')) return grammarError("Missing \'.\', Expected Character Range", pos, errorFlag);
	if (!eat(str, pos, '.')) return grammarError("Missing \'.\', Expected Character Range", pos, errorFlag);
    if (!eat(str, pos, '.')) return grammarError("Missing \'.\', Expected Character Range", pos, errorFlag);
    parseWhiteSpace(str, pos, FALSE);
	if (!eat(str, pos, '\'')) return grammarError("Missing \' quotation mark, Expected Character", pos, errorFlag);
	if (!parseStringToken(str, pos)) return FALSE;
	if (!eat(str, pos, '\'')) return grammarError("Missing \' quotation mark, Expected Character", pos, errorFlag);
	return TRUE;
}


void parseWhiteSpace(char* str, int* pos, int newlines) {
    if (newlines) {
		while (eat(str, pos, ' ') || eat(str, pos, '\t') || eat(str, pos, '\n') || eat(str, pos, '\r'));
	}
    else
    {
        while (eat(str, pos, ' ') || eat(str, pos, '\t') || eat(str, pos, '\r'));
    }
}

void parseComment(char* str, int* pos) {
    if (eat(str, pos, '!') && eat(str, pos, '!')) {
        while (!eat(str, pos, '\n')) {
            (*pos)++;
        };
    }
}

void parseWhiteSpaceAndComments(char* str, int* pos) {
    while (eat(str, pos, ' ') || eat(str, pos, '\t') || eat(str, pos, '\n') || eat(str, pos, '\r') || peek(str, pos, '!')) {
		if (((*pos)+1) < strlen(str) && str[*pos]=='!' && str[(*pos)+1]=='!') {
			parseComment(str, pos);
		}
        else {
            parseWhiteSpace(str, pos, TRUE);
        }
    }
}

int eat(char* str, int* pos, char c) {
	if (((*pos) < strlen(str)) && str[*pos] == c) {
		(*pos)++;
		return TRUE;
	}
	return FALSE;
}

int eatString(char* str, int* pos, char* s) {
	int i;
	for (i = 0; i < strlen(s); i++) {
		if (!eat(str, pos, s[i])) return FALSE;
	}
	return TRUE;
}

int peek(char* str, int* pos, char c) {
	if (((*pos) < strlen(str)) && str[*pos] == c) {
		return TRUE;
	}
	return FALSE;
}

char* substr(char* str, int lower, int upper) {
    if (lower < 0 || upper > strlen(str) ||
        lower > strlen(str) || upper < 0) {
        return NULL;
    }
    // allocate memory for the substring
    char* result = malloc(sizeof(char) * (upper - lower + 1));
    // improper bounds
    if (result == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    // form the substring
    int i = 0;
    while (lower < upper) {
        result[i] = str[lower];
        i++;
        lower++;
    }
    result[i] = '\0';
    return result;
}
