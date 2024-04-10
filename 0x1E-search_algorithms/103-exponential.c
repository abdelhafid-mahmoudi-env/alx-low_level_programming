#include "search_algos.h"

/**
 * exponential_search - Performs exponential search algorithm
 * @array: The integer array
 * @size: Size of the array
 * @value: Value to search for
 *
 * Return: The index found or -1
 */
int exponential_search(int *array, size_t size, int value)
{
	size_t i = 1;
	int ret;
	size_t left, right;

	if (!array || size == 0)
		return (-1);

	while (i < size && array[i] < value)
	{
		printf("Value checked array[%lu] = [%d]\n", i, array[i]);
		i *= 2;
	}

	left = i / 2;
	right = (i < size) ? i : size - 1;

	printf("Value found between indexes [%lu] and [%lu]\n", left, right);

	ret = binary_search(array + left, right - left + 1, value);
	if (ret != -1)
		return (ret + left);

	return (-1);
}

/**
 * binary_search - Searches for a value in a sorted array of integers
 *                using the Binary search algorithm.
 * @array: A pointer to the first element of the array to search in.
 * @size: The number of elements in array.
 * @value: The value to search for.
 *
 * Return: The index where value is located, or -1 if not found or
 *         array is NULL.
 */
int binary_search(int *array, size_t size, int value)
{
	size_t left = 0, right = size - 1, mid;

	if (array == NULL)
		return (-1);

	while (left <= right)
	{
		size_t i;

		printf("Searching in array: ");
		for (i = left; i <= right; i++)
		{
			printf("%d", array[i]);
			if (i < right)
				printf(", ");
		}
		printf("\n");

		mid = (left + right) / 2;

		if (array[mid] == value)
			return (mid);
		else if (array[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return (-1);
}
