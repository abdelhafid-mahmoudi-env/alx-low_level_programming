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
	size_t i, newsize = 0;
	int ret;

	if (!array || size == 0)
		return (-1);

	for (i = 1; i < size && array[i] < value; i <<= 1)
	{
		printf("Value checked array[%lu] = [%d]\n", i, array[i]);
	}

	newsize = (i >= size ? size : i + 1) - (i >> 1);
	i >>= 1;

	printf("Value found between indexes [%lu] and [%lu]\n",
		   i, i << 1 >= size ? size - 1 : i << 1);

	ret = binary_search(array, i + 1, value);
	return (ret == -1 ? ret : ret + (int)i);
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
