#include "search_algos.h"

/**
 * jump_search - Performs jump search algorithm.
 * @array: A pointer to the first element of the array to search.
 * @size: The number of elements in the array.
 * @value: The value to search for.
 *
 * Return: If the value is not present in the array or the array.
 *        
 */
int jump_search(int *array, size_t size, int value)
{
	size_t idx = 0, jmp = sqrt(size);

	if (!array)
		return (-1);

	for (; idx < size && array[idx] < value; idx += jmp)
	{
		printf("Value checked array[%lu] = [%d]\n", idx, array[idx]);
	}

	jmp = idx - jmp;
	printf("Value found between indexes [%lu] and [%lu]\n", jmp, idx);
	idx = idx >= size ? size - 1 : idx;
	for (; jmp <= idx; jmp++)
	{
		printf("Value checked array[%lu] = [%d]\n", jmp, array[jmp]);
		if (array[jmp] == value)
			return (jmp);
	}
	return (-1);
}
