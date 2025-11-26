#include "linkedlist.h"

int main(void)
{
	Node* head = NULL;

	appendNode(&head, 10);
	appendNode(&head, 20);
	appendNode(&head, 30);
	printList(head);
	findNode(head, 1);
	insertNodeAtTarget(&head, findNode(head, 1), 15);
	printList(head);

	removeNode(&head, findNode(head, 2));
	printList(head);
	freeList(head);
	head = NULL;

	return 0;
}