#include <stdio.h>
#include <stdlib.h>
#include "search_algos.h"

/**
 * advanced_binary - Performs advanced binary search algorithm
 * @array: The integer array
 * @size: Size of the array
 * @value: Value to search for
 *
 * Return: The index of the first occurrence of value, or -1 if not found
 */
int advanced_binary(int *array, size_t size, int value)
{
	size_t left, right, mid, i;

	if (array == NULL || size == 0)
		return (-1);

	left = 0;
	right = size - 1;

	while (left <= right)
	{
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
		{
			if (mid == left || array[mid - 1] != value)
				return (mid);
			right = mid;
		}
		else if (array[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return (-1);
}
