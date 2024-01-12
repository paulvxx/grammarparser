#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "charsetlist.h"

int main(int argc, char* argv[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char c = 'a';
	char c2 = 'b';
	char c3 = 'c';
	char c4 = 'd';
	// Create a new character list
	Node* charset = NULL;
	pushCharToCharSet(&charset, &c);
	pushCharToCharSet(&charset, &c2);
	pushCharToCharSet(&charset, &c3);
	pushCharToCharSet(&charset, &c4);
	printCharSet(charset, 0);
	printf("\n");

	char c5 = 'd';
	char c6 = 'e';
	char c7 = 'g';
	// Create a new character list
	Node* charset2 = NULL;
	pushCharToCharSet(&charset2, &c5);
	pushCharToCharSet(&charset2, &c6);
	pushCharToCharSet(&charset2, &c7);
	printCharSet(charset2, 1);
	printf("\n");

	
	Node* charsetList = NULL;

	pushToCharSetList(&charsetList, &charset, 0);
	pushToCharSetList(&charsetList, &charset2, 1);

	printCharSetList(charsetList);

	pop(&charset);
	pop(&charset);
	pop(&charset);
	pop(&charset);

	pop(&charset2);
	pop(&charset2);
	pop(&charset2);

	pop(&charsetList);
	pop(&charsetList);

	return 0;
}
