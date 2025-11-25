#include <stdlib.h>
#include <stdio.h>


/**
 * bubble_sort - 정수 배열을 오름 차순으로 정렬 하는 버블 정렬 알고리즘을 구현합니다.
 * @arr : 정수 배열
 * @arr_size : 배열의 크기
 * Return: 성공시 0, 실패시 -1
*/
int bubble_sort(int arr[], size_t arr_size)
{
    // 입력 유효성 검사
    if (arr == NULL || arr_size == 0)
        return -1;

    // 버블 정렬 알고리즘 구현
    for (size_t i = 0; i < arr_size - 1; i++)
    {
        for (size_t j = 0; j < arr_size - i - 1; j++)
        {
            // 인접한 요소 비교 및 교환
            if (arr[j] > arr[j + 1])
            {
                // 요소 교환
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