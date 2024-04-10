#include "search_algos.h"

/**
 * linear_skip - skippity skip search singular linked list
 * @list: pointer to head node
 * @value: value to search for
 *
 * Return: the node found or NULL
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *current = list;

	if (!list)
		return (NULL);

	while (list->n < value)
	{
		if (!list->express)
			break;
		current = list;
		list = list->express;
		printf("Value checked at index [%lu] = [%d]\n", list->index, list->n);
	}
	if (list->n >= value)
	{
		printf("Value found between indexes [%lu] and [%lu]\n",
				current->index, list->index);
		list = current;
	}
	else
	{
		for (current = list; current->next; current = current->next)
			;
		printf("Value found between indexes [%lu] and [%lu]\n",
				list->index, current->index);
	}
	while (list)
	{
		printf("Value checked at index [%lu] = [%d]\n", list->index, list->n);
		if (list->n == value)
			return (list);
		list = list->next;
	}
	return (NULL);
}
