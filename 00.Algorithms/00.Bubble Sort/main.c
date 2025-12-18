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
    size_t arr_len = arr_size;
    int is_sorted = 0;

    // 버블 정렬 알고리즘 구현
    for (size_t i = 0; i < arr_size - 1; i++)
    {
        is_sorted = 1; // 정렬 여부 플래그 초기화
        for (size_t j = 0; j < arr_len; j++)
        {
            // 인접한 요소 비교 및 교환
            if (arr[j] > arr[j + 1])
            {
                // 요소 교환
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                is_sorted = 0; // 교환이 발생했으므로 정렬되지 않음
            }
        }
        arr_len--; // 마지막 요소는 이미 정렬되었으므로 비교 범위 축소
        // 정렬이 완료되었으면 종료
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