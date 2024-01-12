#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "grammarformatparser.h"

int main(int argc, char* argv[]) {
	char *grammarStr = parseFile("test.txt");
	int pos = 0;
	if (parseGrammar(grammarStr, &pos)) {
		printf("Grammar Format = true\n");
	}
	else {
		printf("Grammar Format = false\n");
	}
	free(grammarStr);
	return 0;
}
