#include <unistd.h>
#include <stdio.h>

#include "ArrayBasedLinearQueue.h"

int main(void)
{
	ArrayBasedLinearQueue queue;
	ElementType item;

	initQueue(&queue);

	enqueue(&queue, 10);
	enqueue(&queue, 20);
	enqueue(&queue, 30);
	displayQueue(&queue);
	printf("\n");
	dequeue(&queue, &item);
	printf("Dequeued: %d\n", item);
	displayQueue(&queue);
	printf("\n");

	enqueue(&queue, 40);
	enqueue(&queue, 50);
	displayQueue(&queue);
	printf("\n");
	int result = enqueue(&queue, 60);
	if (result == -1) {
		printf("Queue is full, cannot enqueue 60\n");
	}
	return 0;
}