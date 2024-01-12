#include <stdio.h>
#include <stdarg.h>

#include <stack.h>
#include <string.h>

// Pushes a character to a character set
// A character set is a stack of characters
void pushToCharSet(Node** charset, char* c);

// A list of Character sets
// Character sets are a form of regular expressions
// If repeats is true (1), the character set may repeated (Kleene star)
// Otherwise, the character set will parse only once (0)
void pushToCharSetList(Node** charsetList, Node** charset, int repeats);

// Prints a character set
// repeated = 1 to print Kleene Start
// otherwise not
void printCharSet(Node* charsetList, int repeated);

// Prints a character set list
void printCharSetList(Node* charsetList);
