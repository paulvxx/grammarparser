#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "charsetlist.h"

// This scans a specific type of regular expression
// which is a sequence of character sets that may or may not 
// repeat 
// e.g. {('1' .. '9')} {('0' .. '9')}*
// 
// returns true if the string matches the regular expression
// returns false otherwise
// str - string to be scanned
// pos - starting position of the string to be scanned
// matchEnd - if true, the entire string must match the regular expression
// otherwise, only a substring (starting at index pos) 
// of the string must match the regular expression
int scanCharSetList(Node **charsetList, char *str, int *pos, int matchEnd);


// scans a signle character set recursively (in the context of a character set list)
// pops a character set from the stack once the string is parsed and matches the character set
// This scans a specific type of regular expression
// which is a sequence of character sets that may or may not 
// repeat 
// e.g. {('1' .. '9')} {('0' .. '9')}*
// 
// this function would scan the first character set in the stack 
// e.g. {('1' .. '9')}
// 
// returns true if the string matches the regular expression
// returns false otherwise
// charsetAt - the index of the character set (in the list) to be scanned
// str - string to be scanned
// pos - starting position of the string to be scanned
// matchEnd - if true, the entire string must match the regular expression
// otherwise, only a substring (starting at index pos) 
// of the string must match the regular expression
int scanCharSet(Node** charsetList, int charsetAt, char* str, int* pos, int matchEnd);

