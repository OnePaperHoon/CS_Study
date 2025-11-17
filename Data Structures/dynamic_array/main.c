#include <stdlib.h>
#include <stdio.h>
#include "darray.h"

void check_leak()
{
	#ifdef __APPLE__
		system("leaks -q algorithm.exe");
	#endif
}

int main(void)
{
	DArray *array = darray_create(sizeof(int), 4);

	int num = 10;
	darray_push_back(array, (void*) &num);

	num = 20;
	array->push_back(array, (void*)&num);
	
	for (size_t i = 0; i < array->size; i++)
	{
		printf("%d\n", *(int *)darray_get(array, i));
	}

	darray_destroy(array);
	return 0;
}