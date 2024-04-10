#include "search_algos.h"

/**
 * recursive_advanced_binary - Performs advanced binary search recursively
 * @array: The integer array
 * @size: The size of the array
 * @value: The value to search for
 *
 * Return: Pointer to the found value or NULL
 */
int *recursive_advanced_binary(int *array, size_t size, int value)
{
	size_t i = 0;

	if (!size || !array)
		return (NULL);

	for (printf("Searching in array: "); i < size; i++)
		printf("%d%s", array[i], i + 1 == size ? "\n" : ", ");

	i = (size - 1) / 2;
	if (array[i] == value)
	{
		if (i)
			return (recursive_advanced_binary(array, i + 1, value));
		return (array + i);
	}
	else if (array[i] > value)
		return (recursive_advanced_binary(array, i + 1, value));
	else
		return (recursive_advanced_binary(array + i + 1, size - i - 1, value));
}

/**
 * advanced_binary - Performs advanced binary search
 * @array: The integer array
 * @size: The size of the array
 * @value: The value to search for
 *
 * Return: The index found or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	int *a = recursive_advanced_binary(array, size, value);

	if (!a)
		return (-1);
	else
		return (a - array);
}
