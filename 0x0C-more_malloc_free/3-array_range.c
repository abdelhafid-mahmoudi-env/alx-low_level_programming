#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * array_range - Create an array of integers from min to max (inclusive).
 * @min: The starting number.
 * @max: The ending number.
 *
 * Return: A pointer to the allocated memory
 * containing the array, or NULL on failure.
 */
int *array_range(int min, int max)
{
	int *arr, size, i;

	if (min > max)
		return (NULL);

	size = max - min + 1;
	arr = malloc(sizeof(int) * size);

	if (!arr)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		arr[i] = min;
		min++;
	}

	return (arr);
}

