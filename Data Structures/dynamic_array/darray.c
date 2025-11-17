#include "darray.h"

/**
 * Creates a new dynamic array.
 * 
 * @param element_size Size of each element in bytes.
 * @param initial_capacity Initial capacity of the dynamic array.
 * @return Pointer to the created DArray, or NULL on failure.
 */

DArray	*darray_create(size_t element_size, size_t initial_capacity)
{
	// Validate input parameters
	if (initial_capacity <= 0 || element_size == 0)
		return NULL;
	
	// Allocate memory for the DArray Structure
	DArray *array = (DArray *)malloc(sizeof(DArray));

	// Check if memory allocation was successful
	if (!array)
	{
		errno = ENOMEM;
		return NULL;
	}
	
	// Allocate memory for the data buffer
	array->data = malloc(element_size * initial_capacity);

	// Initialize the DArray fields
	if (!array->data)
	{
		free(array);
		errno = ENOMEM;
		return NULL;
	}
	array->capacity = initial_capacity;
	array->size = 0;
	array->element_size = element_size;

	// Assign function pointers
	array->push_back = darray_push_back;
	array->insert = darray_insert;
	array->remove = darray_remove;
	array->get = darray_get;
	return array;
}

void darray_destroy(DArray *array)
{
	if (array)
	{
		free(array->data);
		free(array);
	}
}

int darray_push_back(DArray *array, void *element)
{
	// Check if resizing is needed
	if (array->size >= array->capacity)
	{
		// Double the capacity
		size_t new_capacity = array->capacity * 2;

		// Reallocate memory for the data buffer
		void *new_data = realloc(array->data, new_capacity * array->element_size);

		// Check if reallocation was successful
		if (!new_data)
			return -1;
		
		// Update the array with the new data buffer and capacity
		array->data = new_data;
		array->capacity = new_capacity;
	}
	// Copy the new element to the end of the array
	char *dest = (char *)array->data + (array->size * array->element_size);

	// Use memcpy to copy the element data
	memcpy(dest, element, array->element_size);

	// Increment the size of the array
	array->size++;
	return 0;
}

void darray_insert(DArray *array, size_t index, void *element)
{
	if (index > array->size)
		return;

	// Resize if necessary
	if (array && array->size >= array->capacity)
	{
		// Double the capacity
		size_t new_capacity = array->capacity * 2;
		
		// Reallocate memory for the data buffer
		void *new_data = realloc(array->data, new_capacity * array->element_size);

		// Check if reallocation was successful
		if (!new_data)
			return ;
		
		// Update the array with the new data buffer and capacity
		array->data = new_data;
		array->capacity = new_capacity;
	}
	// Shift elements to the right
	char *dest = (char *)array->data + (index * array->element_size);
	memmove(dest + array->element_size, dest, (array->size - index) * array->element_size);
	
	// Insert the new element
	memcpy(dest, element, array->element_size);
	array->size++;
}

void darray_remove(DArray *array, size_t index)
{
	// Check for valid index
	if (index >= array->size)
		return;
	
	// Shift elements to the Left
	char *dest = (char *)array->data + (index * array->element_size);
	memmove(dest, dest + array->element_size, (array->size - index - 1) * array->element_size);

	array->size--;
}

void *darray_get(DArray *array, size_t index)
{
	// Check for valid index
	if (index >= array->size)
		return NULL;

	// Return pointer to the requested element
	void *result = (char *)array->data + (index * array->element_size);
	
	return result;
}

size_t darray_size(DArray *array)
{
	return array->size;
}

size_t darray_capacity(DArray *array)
{
	return array->capacity;
}