#include "darray.h"

DArray	*darray_create(size_t element_size, size_t initial_capacity)
{
	// Allocate memory for the DArray Structure
	DArray *array = (DArray *)malloc(sizeof(DArray));

	// Check if memory allocation was successful
	if (!array)
		return errno = ENOMEM, NULL;
	
	// Allocate memory for the data buffer
	array->data = malloc(element_size * initial_capacity);

	// Initialize the DArray fields
	if (!array->data)
	{
		free(array);
		return errno = ENOMEM, NULL;
	}
	array->capacity = initial_capacity;
	array->size = 0;
	array->element_size = element_size;

	return array;
}