#include "doubleLinkedList.h"

int main(void)
{
	Node* Head = NULL;

	addNode(&Head, 20);

	printList(&Head);
	
	return 0;
}