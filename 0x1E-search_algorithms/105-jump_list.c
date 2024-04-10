#include "search_algos.h"

/**
 * jump_list - Searches for a value in a sorted list of integers using the
 *             Jump search algorithm.
 * @list: A pointer to the head of the list to search in.
 * @size: The number of nodes in the list.
 * @value: The value to search for.
 *
 * Return: A pointer to the first node where value is located, or NULL if value
 *         is not present or if the list is empty.
 */
listint_t *jump_list(listint_t *list, size_t size, int value)
{
	size_t step, prev_idx;
	listint_t *current, *prev;

	if (!list)
		return (NULL);

	step = sqrt(size);
	current = list;
	prev = NULL;

	while (current && current->n < value)
	{
		prev = current;
		prev_idx = current->index;
		for (size_t i = 0; current->next && i < step; i++)
			current = current->next;
		printf("Value checked at index [%lu] = [%d]\n", current->index, current->n);
	}

	printf("Value found between indexes [%lu] and [%lu]\n", prev_idx, current->index);
	printf("Value checked at index [%lu] = [%d]\n", prev_idx, prev->n);
	while (prev && prev->n < value)
	{
		printf("Value checked at index [%lu] = [%d]\n", prev->index, prev->n);
		prev = prev->next;
	}

	if (prev && prev->n == value)
		return (prev);

	return (NULL);
}
