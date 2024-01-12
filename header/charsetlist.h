#include <stdio.h>
#include <stdarg.h>

#include <stack.h>
#include <string.h>

// Adds a character to the current set (as a stack)
void pushToCharSet(Node** charset, char* c) {
	Data data;
	data.type = "character";
	data.data = c;
	push(charset, data);
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
	push(charsetList, data);
};
