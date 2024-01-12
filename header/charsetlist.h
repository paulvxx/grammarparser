#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "stack.h"

typedef struct Range {
	char min;
	char max;
} Range;

// Pushes a character to a character set
// A character set is a stack of characters
void pushCharToCharSet(Node** charset, char* c);

// Pushes a character range to a character set
// A character set is a stack of characters
void pushRangeToCharSet(Node** charset, char* end1, char* end2);

// Pushes a range to a character set
// A character range is a range of characters
// min and max are inclusive
void pushRangeToCharSet(Node** charset, char* min, char *max);

// A list of Character sets
// Character sets are a form of regular expressions
// If repeats is true (1), the character set may repeated (Kleene star)
// Otherwise, the character set will parse only once (0)
void pushToCharSetList(Node** charsetList, Node** charset, int repeats);

// deletes the entire Character Set
void deleteAllCharSet(Node** charset);

// deletes the first element of the Character Set
void popChar(Node** charset);

// deletes the entire Character set list
void deleteAllCharSetList(Node** charsetList);

// deletes the first character set of the character set list
void popCharSet(Node** charsetList);

// Prints a character set
// repeated = 1 to print Kleene Start
// otherwise not
void printCharSet(Node* charsetList, int repeated);

// Prints a character set list
void printCharSetList(Node* charsetList);
