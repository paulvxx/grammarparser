#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include <crtdbg.h>

#include "grammarformatparser.h"

int main(int argc, char* argv[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//char *grammarStr = parseFile("test.txt");
	//int pos = 0;
	//if (parseGrammar(grammarStr, &pos)) {
	//	printf("Grammar Format = true\n");
	//}
	//else {
	//	printf("Grammar Format = false\n");
	//}
	//free(grammarStr);

	Node* list = NULL;
	int a = 2;
	int b = 3;
	int c = 4;
	Data data = { "int" , &a };
	Data data2 = { "int" , &b };
	Data data3 = { "int" , &c };

	push(&list, data);
	push(&list, data2);
	push(&list, data3);

	printf("Before deletion: \n");
	Node* it = list;
	while (it != NULL) {
		printf("%d ->", *(int*)(it->data.data));
		it = it->next;
	}

	pop_back(&list);
	printf("\n");
	it = list;
	// print the list
	printf("After deletion: \n");
	printf("Size: %d\n", size(list));
	int i = 0;
	while (it != NULL) {
		printf("%d ", i);
		printf("%d ->", *(int*)(it->data.data));
		it = it->next;
		i++;
	}


	return 0;
}
