#include "PriorityQueue.h"

// Create a priority queue with given capacity
PriorityQueue* create_priority_queue(size_t capacity)
{
	if (capacity == 0)
		return NULL;

	PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	if (!pq)
		return NULL;

	pq->data = (int *)malloc(sizeof(int) * capacity);
	if (!pq->data)
	{
		free(pq);
		return NULL;
	}

	pq->capacity = capacity;
	pq->size = 0;

	return pq;
}

// Destroy the priority queue and free memory
void destroy_priority_queue(PriorityQueue *pq)
{
	if (pq)
	{
		if (pq->data)
			free(pq->data);
		free(pq);
	}
}

// Check if the Priority Queue is empty
bool is_empty(PriorityQueue *pq)
{
	return pq->size == 0;
}

// Check if the Priority Queue is full
bool is_full(PriorityQueue *pq)
{
	return pq->size == pq->capacity;
}

// Enqueue an element into the priority queue
void enqueue(PriorityQueue *pq, int value)
{
	if (is_full(pq))
	{
		pq = pq_resize(pq, pq->capacity * 2);
	}
	pq->data[pq->size] = value;
	pq->size++;
	heapify_up(pq, pq->size - 1);
}

// Dequeue the highest priority element from the priority queue
int dequeue(PriorityQueue *pq)
{
	if (is_empty(pq))
		return INT_MIN;

	int root = pq->data[0];
	pq->data[0] = pq->data[pq->size - 1];
	pq->size--;
	heapify_down(pq, 0);

	if (pq->size > 0 && pq->size == pq->capacity / 4)
	{
		pq = pq_resize(pq, pq->capacity / 2);
	}

	return root;
}

// Peek at the highest priority element without removing it
int peek(PriorityQueue *pq)
{
	if (is_empty(pq))
		return INT_MIN;
	return pq->data[0];
}

// Heapify up to maintain max-heap property
void heapify_up(PriorityQueue *pq, size_t index)
{
	if (index == 0)
		return ;
	
	size_t pa_index = parent_index(index);
	if (cmp(&pq->data[index], &pq->data[pa_index]) > 0)
	{
		swap(&pq->data[index], &pq->data[pa_index]);
		heapify_up(pq, pa_index);
	}
	else
	{
		return ;
	}
}

// Heapify down to maintain max-heap property
void heapify_down(PriorityQueue *pq, size_t index)
{
	size_t left_ch_index = left_child_index(index);
	size_t right_ch_index = right_child_index(index);
	size_t largest_index = index;

	if (left_ch_index < pq->size && cmp(&pq->data[left_ch_index], &pq->data[largest_index]) > 0)
	{
		largest_index = left_ch_index;
	}
	if (right_ch_index < pq->size && cmp(&pq->data[right_ch_index], &pq->data[largest_index]) > 0)
	{
		largest_index = right_ch_index;
	}

	if (largest_index != index)
	{
		swap(&pq->data[index], &pq->data[largest_index]);
		heapify_down(pq, largest_index);
	}
	else
	{
		return ;
	}
}

// Resize the priority queue to a new capacity
PriorityQueue* pq_resize(PriorityQueue *pq, size_t new_capacity)
{
	if (new_capacity < pq->size)
		return pq;

	int *new_data = (int *)realloc(pq->data, sizeof(int) * new_capacity);
	if (new_data == NULL)
		return pq;
	pq->data = new_data;
	pq->capacity = new_capacity;

	return pq;
}

/* Helper functions */
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Comparison function for max-heap
int cmp(const int *a, const int *b)
{
	return (*a - *b);
}

// Index calculation functions
size_t parent_index(size_t index)
{
	return (index - 1) / 2;
}

size_t left_child_index(size_t index)
{
	return 2 * index + 1;
}

size_t right_child_index(size_t index)
{
	return 2 * index + 2;
}

void show_priority_queue(PriorityQueue *pq)
{
	if (is_empty(pq))
	{
		printf("Priority Queue is empty\n");
		return;
	}

	printf("\nPriority Queue (Max Heap) Structure:\n");
	printf("=====================================\n");

	// Calculate the height of the heap
	int height = 0;
	size_t temp = pq->size;
	while (temp > 0)
	{
		height++;
		temp >>= 1;
	}

	// Print level by level
	size_t index = 0;
	for (int level = 0; level < height && index < pq->size; level++)
	{
		int nodes_in_level = 1 << level;
		int edge_spacing = (1 << (height - level - 1)) - 1;
		int node_spacing = (1 << (height - level)) - 1;

		// Print leading spaces
		for (int i = 0; i < edge_spacing + edge_spacing / 2; i++)
			printf(" ");

		// Print nodes in this level
		for (int i = 0; i < nodes_in_level && index < pq->size; i++)
		{
			if (i > 0)
			{
				for (int j = 0; j < node_spacing + node_spacing / 2 + 1; j++)
					printf(" ");
			}
			printf("%2d", pq->data[index]);
			index++;
		}
		printf("\n");

		// Print connection lines if not the last level
		if (level < height - 1 && index < pq->size)
		{
			size_t level_start = (1 << level) - 1;
			int branch_spacing = (1 << (height - level - 2));

			// Print leading spaces for branches
			for (int i = 0; i < edge_spacing - branch_spacing + (edge_spacing - branch_spacing) / 2; i++)
				printf(" ");

			size_t current_index = level_start;
			for (int i = 0; i < nodes_in_level && current_index < pq->size; i++)
			{
				if (i > 0)
				{
					int gap = node_spacing - branch_spacing * 2;
					for (int j = 0; j < gap + gap / 2 + 1; j++)
						printf(" ");
				}

				size_t left_idx = left_child_index(current_index);
				size_t right_idx = right_child_index(current_index);

				// Left branch
				if (left_idx < pq->size)
					printf("/");
				else
					printf(" ");

				// Middle spacing
				for (int j = 0; j < branch_spacing * 2 + branch_spacing; j++)
					printf(" ");

				// Right branch
				if (right_idx < pq->size)
					printf("\\");
				else
					printf(" ");

				current_index++;
			}
			printf("\n");
		}
	}
	printf("=====================================\n\n");
}