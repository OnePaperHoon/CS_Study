#include <stdlib.h>
#include <stdio.h>

int bubble_sort(int arr[], size_t arr_size)
{
    if (arr == NULL || arr_size == 0)
        return -1;

    for (size_t i = 0; i < arr_size - 1; i++)
    {
        for (size_t j = 0; j < arr_size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return 0;
}

int main(void)
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    if (bubble_sort(arr, arr_size) != 0)
        return EXIT_FAILURE;

    for (size_t i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);

    return EXIT_SUCCESS;
}