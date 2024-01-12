#include <stdio.h>
#include <stdarg.h>

#define TRUE 1
#define FALSE 0
#include <string.h>
#include "charsetlist.h"

// Adds a character to the current set (as a stack) 
void pushCharToCharSet(Node** charset, char* c) {
	Data data;
	data.type = "character";
	data.data = (void*) c;
	push_back(charset, data);
}

void pushRangeToCharSet(Node** charset, char* end1, char* end2) {
	Range *r = (Range*) malloc(sizeof(Range));
	if (end1[0] > end2[0]) {
		r->min = (*end2);
		r->max = (*end1);
	}
	else {
		r->min = (*end1);
		r->max = (*end2);
	}
	Data data;
	data.type = "range";
	data.data = (void*) r;
	push_back(charset, data);
}


void pushToCharSetList(Node** charsetList, Node** charset, int repeats) {
	Data data;
	if (repeats) {
		data.type = "repeated";
	}
	else {
		data.type = "charset";
	}
	data.data = charset;
	push_back(charsetList, data);
};


void deleteAllCharSet(Node** charset) {
	while (!isEmpty(*charset)) {
		popChar(charset);
	}
}


void popChar(Node** charset) {
	Data data = pop(charset);
	if (strcmp(data.type, "range") == 0) {
		Range* r = (Range*)data.data;
		free(r);
	}
}


void deleteAllCharSetList(Node** charsetList) {
	while (!isEmpty(*charsetList)) {
		popCharSet(charsetList);
	}
}

// deletes the first character set of the character set list
void popCharSet(Node** charsetList) {
	deleteAllCharSet((Node**)(*charsetList)->data.data);
	pop(charsetList);
}

// Prints a character set
void printCharSet(Node* charsetList, int repeated) {
Node* current = charsetList;
	printf("{");
	while (current != NULL) {
		if (strcmp(current->data.type, "character") == 0) {
			printf("\'%c\'", *(char*) current->data.data);
			if (current->next != NULL) printf(", ");
		}
		else if (strcmp(current->data.type, "range") == 0) {
			Range r = *(Range*) current->data.data;
			int minesc = r.min == '\a' || r.min == '\b' || r.min == '\f' || r.min == '\n' ||
				r.min == '\r' || r.min == '\t' || r.min == '\v' || r.min == '\?' ||
				r.min == '\\' || r.min == '\'' || r.min == '\"';
			int maxesc = r.max == '\a' || r.max == '\b' || r.max == '\f' || r.max == '\n' ||
				r.max == '\r' || r.max == '\t' || r.max == '\v' || r.max == '\?' ||
				r.max == '\\' || r.max == '\'' || r.max == '\"';

			// used to properly print escaped characters
			if (minesc) {
				// min and max are both escaped
				if (maxesc) {
					printf("(\'\\%c\' ... \'\\%c\')", r.min, r.max);
				}
				// only min is escaped
				else {
					printf("(\'\\%c\' ... \'%c\')", r.min, r.max);
				}
			}
			// only max is escaped
			else if (maxesc) {
				printf("(\'%c\' ... \'\\%c\')", r.min, r.max);
			}
			// neither are escaped
			else {
				printf("(\'%c\' ... \'%c\')", r.min, r.max);
			}
			//printf("\'%c\' - \'%c\'", r.min, r.max);
			if (current->next != NULL) printf(", ");
		}
		else {
			printf("Unknown type: %s", current->data.type);
			if (current->next != NULL) printf(", ");
		}
		current = current->next;
	}
	printf("}");
	if (repeated) {
		printf("*");
	}
}

// Prints a character set list
void printCharSetList(Node* charsetList) {
	Node* current = charsetList;
	while (current != NULL) {
		if (strcmp(current->data.type, "repeated") == 0) {
			printCharSet(*(Node**) current->data.data, 1);
			printf(" ");
		}
		else if (strcmp(current->data.type, "charset") == 0) {
			printCharSet(*(Node**) current->data.data, 0);
			printf(" ");
		}
		else {
			printf("Unknown type: %s", current->data.type);
			printf(" ");
		}
		current = current->next;
	}
	printf("\n");
}
