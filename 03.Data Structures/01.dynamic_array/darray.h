#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef struct DArray
{
	void *data;
	size_t capacity;
	size_t size;
	size_t element_size;
	int (*push_back)(struct DArray *self, void *element);
	void (*insert)(struct DArray *self, size_t, void *);
	void (*remove)(struct DArray *self, size_t index);
	void *(*get)(struct DArray *self, size_t index);
} DArray;

DArray	*darray_create(size_t element_size, size_t initial_capacity);
void 	darray_destroy(DArray *array);
int 	darray_push_back(DArray *array, void *element);
void 	darray_insert(DArray *array, size_t index, void *element);
void 	darray_remove(DArray *array, size_t index);
void 	*darray_get(DArray *array, size_t index);
size_t	darray_size(DArray *array);
size_t	darray_capacity(DArray *array);


#endif