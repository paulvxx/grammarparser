#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "grammarformatparser.h"

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char* toParse = parseFile("test.txt");
	int error = TRUE;
	int pos = 0;
	if (parseGrammar(toParse, &pos, &error)) {
		printf("Grammar is valid\n");
	}
	else {
		printf("Grammar is invalid\n");
	}
	return 0;
}
