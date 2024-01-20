#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef  STRING_UTILS_H
#define STRING_UTILS_H

// used to obtain a substring from a string
char* substr(char* str, int lower, int upper);

// used to process escape characters in a string
void processEscapeCharacters(char** strToProcess);

#endif STRING_UTILS_H