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

	char c8 = '0';
	char c9 = '9';
	pushRangeToCharSet(&charset2, &c8, &c9);
	
	Node* charsetList = NULL;

	pushToCharSetList(&charsetList, &charset, 0);
	pushToCharSetList(&charsetList, &charset2, 1);

	printCharSetList(charsetList);

	printf("size; %d\n", size(charsetList));

	popCharSet(&charsetList);
	//deleteAllCharSet(&charset2);
	deleteAllCharSetList(&charsetList);

	//pop(&charset);
	//pop(&charset);
	//pop(&charset);
	//pop(&charset);

	//pop(&charset2);
	//pop(&charset2);
	//pop(&charset2);
	//Data rng = pop(&charset2);
	//if (rng.type == "range") {
	//	printf("Range: %c - %c\n", ((Range*)rng.data)->min, ((Range*)rng.data)->max);
	//	Range* r = (Range*)rng.data;
	//	free(r);
	//	pop(&charset2);
	//};

	//printf("%s\n", d->type);

	//Data *d = pop(&charset2);
	//free(d->data);
	//pop(&charsetList);
	//pop(&charsetList);

	return 0;
}
