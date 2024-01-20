#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringutils.h"

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

void processEscapeCharacters(char** strToProcess) {
	int i = 0;
	int j = 0;
	char* str = *strToProcess;
	char* result = malloc(sizeof(char) * (strlen(str) + 1));
	if (result == NULL) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	while (i < strlen(str)) {
		if (str[i] == '\\') {
			i++;
			if (str[i] == 'a') {
				result[j] = '\a';
			}
			else if (str[i] == 'b') {
				result[j] = '\b';
			}
			else if (str[i] == 'f') {
				result[j] = '\f';
			}
			else if (str[i] == 'n') {
				result[j] = '\n';
			}
			else if (str[i] == 'r') {
				result[j] = '\r';
			}
			else if (str[i] == 't') {
				result[j] = '\t';
			}
			else if (str[i] == 'v') {
				result[j] = '\v';
			}
			else if (str[i] == '?') {
				result[j] = '\?';
			}
			else if (str[i] == '\\') {
				result[j] = '\\';
			}
			else if (str[i] == '\'') {
				result[j] = '\'';
			}
			else if (str[i] == '\"') {
				result[j] = '\"';
			}
			else {
				result[j] = str[i];
			}
		}
		else {
			result[j] = str[i];
		}
		i++;
		j++;
	}
	result[j] = '\0';
	// save memory by reallocating
	char* temp = realloc(str, sizeof(char) * (strlen(result) + 1));
	if (temp == NULL) {
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	str = temp;
	strcpy(str, result);
	*strToProcess = str;
	free(result);
}