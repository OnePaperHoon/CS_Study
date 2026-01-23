#include "PriorityQueue.h"
#include <stdlib.h>

int main(void)
{
	// Create a priority queue with initial capacity of 10
	PriorityQueue *pq = create_priority_queue(10);
	if (!pq)
		return EXIT_FAILURE;

	// Enqueue elements into the priority queue
	enqueue(pq, 5);
	enqueue(pq, 10);
	enqueue(pq, 3);
	enqueue(pq, 8);
	enqueue(pq, 15);
	enqueue(pq, 1);
	enqueue(pq, 7);

	// Dequeue elements and print them
	show_priority_queue(pq);
	printf("Dequeue elements in order:\n");

	// Clean up
	destroy_priority_queue(pq);
	return EXIT_SUCCESS;
}

/* 

Expected Output:
Output:15 10 7 5 8 1 3 
Dequeue elements in order:15 10 8 7 5 3 1
		    15
		10	   7
     5     8  1   3

*/