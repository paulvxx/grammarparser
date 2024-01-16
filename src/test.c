#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "charsetscanner.h"

int smain1(int argc, char* argv[]) {

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

	char c5 = 'e';
	char c6 = 'f';
	char c7 = 'g';
	// Create a new character list
	Node* charset2 = NULL;
	pushCharToCharSet(&charset2, &c5);
	pushCharToCharSet(&charset2, &c6);
	pushCharToCharSet(&charset2, &c7);
	printf("\n");

	char c8 = 'h';
	char c9 = 'z';
	pushRangeToCharSet(&charset2, &c8, &c9);
	printCharSet(charset2, 1);
	printf("\n\n");

	Node* charsetList = NULL;


	char c10 = 'e';
	char c11 = 'f';
	char c12 = 'g';
	// Create a new character list
	Node* charset3 = NULL;
	pushCharToCharSet(&charset3, &c10);
	pushCharToCharSet(&charset3, &c11);
	pushCharToCharSet(&charset3, &c12);
	printCharSet(charset3, 0);
	printf("\n");

	pushToCharSetList(&charsetList, charset, 0);
	pushToCharSetList(&charsetList, charset2, 1);
	pushToCharSetList(&charsetList, charset3, 0);

	printCharSetList(charsetList);

	//printf("size; %d\n", size(charsetList));


	int pos = 0;

	//Node* s = charsetList;

	Node* charset21 = (Node*)get(charsetList, 0).data;
	char* repeats = get(charsetList, 0).type;

	//printCharSet(charset21, strcmp(repeats, "repeated") == 0);

	//int i = 0;
	//while (s != NULL) {
	//		printCharSet(s->data.data, i);
	//		i++;
	//		s = s->next;
	//}

	// print each of the elements of charsetList
	//printCharSet( get(&charsetList, 0).data, 0);
	//printCharSet( get(&charsetList, 1).data, 1);

	int a = scanCharSet(&charsetList, 0, "aeefge", &pos, 1);

	if (a) printf("Found a match\n");
	else printf("No match\n");

	// FREE MEMORY

	//popCharSet(&charsetList);
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
