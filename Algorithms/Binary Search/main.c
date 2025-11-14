#include <stdio.h>

int binary_search(int arr[], int size, int target)
{
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;

		if (arr[mid] == target)
			return mid;
		else if (arr[mid] < target)
			left = mid + 1; // mid + 1 을 하는 이유는 mid는 이미 검사 했기 때문에 제외 할수 있음.
		else
			right = mid - 1;
	}

	return -1; // Target 을 찾지 못함
}

int main()
{
	int arr[] = {0, 5, 6, 10, 14, 16, 18, 20, 21, 26, 27, 37, 42, 44, 48, 50, 53, 55, 60, 65};
	int size = sizeof(arr) / sizeof(arr[0]);

	int target = 20;
	int result = binary_search(arr, size, target);

	printf("Target %d found at index: %d\n", target, result);
	return 0;
}
