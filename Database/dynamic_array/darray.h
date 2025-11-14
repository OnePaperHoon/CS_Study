#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct DArray
{
	void *data;
	size_t capacity;
	size_t size;
	size_t element_size;
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