#include "search_algos.h"

/**
 * recursive_advanced_binary - Searches for a value in a sorted integer array.
 * @array: A pointer to the first element of the array to search in.
 * @size: The number of elements in the array.
 * @value: The value to search for.
 *
 * Return: A pointer to the found value in the array, or NULL if not found.
 */
int *recursive_advanced_binary(int *array, size_t size, int value)
{
	size_t index = 0;

	if (!size || !array)
		return (NULL);

	for (printf("Searching in array: "); index < size; index++)
		printf("%d%s", array[index], index + 1 == size ? "\n" : ", ");

	index = (size - 1) / 2;
	if (array[index] == value)
	{
		if (index)
			return (recursive_advanced_binary(array, index + 1, value));
		return (array + index);
	}
	else if (array[index] > value)
		return (recursive_advanced_binary(array, index + 1, value));
	else
		return (recursive_advanced_binary(
				array + index + 1,
				size - index - 1,
				value
			));
}

/**
 * advanced_binary - Searches for a value in a sorted integer array using
 *                   advanced binary search.
 * @array: A pointer to the first element of the array to search in.
 * @size: The number of elements in the array.
 * @value: The value to search for.
 *
 * Return: The index of the found value in the array, or -1 if not found.
 */
int advanced_binary(int *array, size_t size, int value)
{
	int *num = recursive_advanced_binary(array, size, value);

	if (!num)
		return (-1);
	else
		return (num - array);
}
