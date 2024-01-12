#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

#include "charsetscanner.h"


int scanCharSet(Node** charsetList, int charsetAt, char* str, int* pos, int matchEnd) {
	if (isEmpty(*charsetList)) return TRUE;
	if (charsetAt < 0 || charsetAt > size(charsetList)) return FALSE;

	// no more character sets left to scan
	// if matchEnd is true, then return whether or 
	// not the end of the string was reached
	// otherwise just return TRUE
	if (charsetAt == size(charsetList)) {
		if (matchEnd) return (strlen(str) == pos);
		else return TRUE;
	}

	Node* charset = get(charsetList, charsetAt).data;
	char *repeats = get(charsetList, charsetAt).type;

	// if charset is empty, return false
	if (isEmpty(charset)) return FALSE;

	// check for repeating character set

	// scan multiple characters from set
	if (strcmp("repeated", repeats) == 0) {
		int oldPos = (*pos);
		// backtrack since we are allowed to read
		// any number of characters
		if (scanCharSet(charsetList, charsetAt + 1, str, pos, matchEnd)) return TRUE;
		(*pos) = oldPos;

		int NoneLeft = FALSE;
		while ((*pos) < strlen(str) && !NoneLeft) {
			int charMatched = FALSE;
			// scan the string once
			Node* curr = charset;
			while (curr != NULL && !charMatched) {
				Data data = curr->data;
				if (strcmp(data.type, "range") == 0) {
					Range* r = (Range*)data.data;
					if (str[(*pos)] >= r->min && str[(*pos)] <= r->max) {
						charMatched = TRUE;
					}
				}
				else {
					char* c = (char*)data.data;
					if (str[(*pos)] == (*c)) {
						charMatched = TRUE;
					}
				}
				curr = curr->next;
			}
			NoneLeft = !charMatched;
			(*pos)++;
			oldPos = (*pos);
			if (scanCharSet(charsetList, charsetAt + 1, str, pos, matchEnd)) return TRUE;
			(*pos) = oldPos;
		}
	}
	// scan single character from set
	else {
		if ((*pos) < strlen(str)) return FALSE;
		int charMatched = FALSE;
		// scan the string once
		Node* curr = charset;
		while (curr != NULL && !charMatched) {
			Data data = curr->data;
			if (strcmp(data.type, "range") == 0) {
				Range* r = (Range*)data.data;
				if (str[(*pos)] >= r->min && str[(*pos)] <= r->max) {
					charMatched = TRUE;
				}
			}
			else {
				char* c = (char*)data.data;
				if (str[(*pos)] == (*c)) {
					charMatched = TRUE;
				}
			}
			curr = curr->next;
		}
		if (!charMatched) return FALSE;
		(*pos)++;
		// scan the next character set
		return scanCharSet(charsetList, charsetAt + 1, str, pos, matchEnd);
	}
	printf("Never should be reached!\n");
	return FALSE;
}

