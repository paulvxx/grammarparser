#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "charsetlist.h"

int main(int argc, char* argv[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// Create a new character list
	Node* charsetList = NULL;
	push_back(&charsetList, (Data) { "character", (void*)'a' });
	push_back(&charsetList, (Data) { "character", (void*)'b' });
	push_back(&charsetList, (Data) { "character", (void*)'c' });
	push_back(&charsetList, (Data) { "character", (void*)'d' });
	printCharSet(charsetList, 0);
	printf("\n");
	return 0;
}
