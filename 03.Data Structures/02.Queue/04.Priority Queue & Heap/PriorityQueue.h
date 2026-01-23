#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

// Priority Queue using array-based Max Heap Make C language

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct PriorityQueue {
	int *data;
	size_t capacity;
	size_t size;
} PriorityQueue;

PriorityQueue* create_priority_queue(size_t capacity);
void destroy_priority_queue(PriorityQueue *pq);
bool is_empty(PriorityQueue *pq);
bool is_full(PriorityQueue *pq);
void enqueue(PriorityQueue *pq, int value);
int dequeue(PriorityQueue *pq);
int peek(PriorityQueue *pq);
void heapify_up(PriorityQueue *pq, size_t index);
void heapify_down(PriorityQueue *pq, size_t index);
PriorityQueue* pq_resize(PriorityQueue *pq, size_t new_capacity);

/* Helper functions */
void swap(int *a, int *b);
int cmp(const int *a, const int *b);

size_t parent_index(size_t index);
size_t left_child_index(size_t index);
size_t right_child_index(size_t index);

void show_priority_queue(PriorityQueue *pq);

#endif