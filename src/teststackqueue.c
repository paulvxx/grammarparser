#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "stack.h"

int main1(int argc, char* argv[]) {

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

	//Node* list = NULL;
	//int a = 2;
	//int b = 3;
	//int c = 4;
	//Data data = { "int" , &a };
	//Data data2 = { "int" , &b };
	//Data data3 = { "int" , &c };

	//push(&list, data);
	//push(&list, data2);
	//push(&list, data3);

	//Node* it = list;
	//while (it != NULL) {
	//	printf("%d ->", *(int*)(it->data.data));
	//	it = it->next;
	//}

	//pop_back(&list);
	//pop_back(&list);
	//pop_back(&list);
	//pop(&list);
	//printf("\n");
	//it = list;
	// print the list
	//while (it != NULL) {
	//	printf("%d ->", *(int*)(it->data.data));
	//	it = it->next;
	//}

	int d = 33;
	int d2 = 129;
	int d3 = 111;
	int d4 = 100;
	Data data = { "integer", &d };
	Data data2 = { "integer", &d2 };
	Data data3 = { "integer", &d3 };
	Data data4 = { "integer", &d4 };

	Node* stack = NULL;
	push(&stack, data);
	push(&stack, data2);
	push(&stack, data3);
	push(&stack, data4);

	get(&stack, 0);

	printf("%d\n", *(int*)get(&stack, 2).data);

	pop(&stack);
	pop(&stack);
	pop(&stack);
	pop(&stack);

	return 0;
}
