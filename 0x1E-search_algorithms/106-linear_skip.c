#include "search_algos.h"

/**
 * linear_skip - searches for a value in a sorted skip list of integers
 * @list: pointer to the head of the skip list
 * @value: value to search for
 *
 * Return: pointer to the node with the desired value.
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *current = list, *express_node = NULL, *last_node;

	if (!list)
		return (NULL);

	while (current->express && current->n < value)
	{
		express_node = current->express;
		printf(
				"Value checked at index [%lu] = [%d]\n",
				express_node->index, express_node->n);
		if (express_node->n >= value)
			break;
		current = express_node;
	}

	if (!current->express)
	{
		last_node = current;
		while (last_node->next)
			last_node = last_node->next;
		printf("Value found between indexes [%lu] and [%lu]\n",
			   current->index, last_node->index);
		current = last_node;
	}
	else
	{
		printf("Value found between indexes [%lu] and [%lu]\n",
			   current->index, express_node->index);
	}

	while (current)
	{
		printf("Value checked at index [%lu] = [%d]\n", current->index, current->n);
		if (current->n == value)
			return (current);
		current = current->next;
	}

	return (NULL);
}
