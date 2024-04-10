#include "search_algos.h"

/**
 * linear_skip - searches for a value in a sorted skip list.
 * @list: pointer to the head of the skip list
 * @value: value to search for
 *
 * Return: pointer to the node with the desired value
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
