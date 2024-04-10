#include "search_algos.h"

/**
 * linear_skip - searches for a value in a sorted skip list of integers
 * @list: pointer to the head of the skip list
 * @value: value to search for
 *
 * Return: pointer to the node with the desired value, or NULL if not found
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *current = list, *express_node = NULL;

	if (!list)
		return (NULL);

	while (current->express && current->n < value)
	{
		express_node = current->express;
		printf("Value checked at index [%lu] = [%d]\n",
			   express_node->index, express_node->n);
		if (express_node->n >= value)
			break;
		current = express_node;
	}

	if (!current->express)
	{
		while (current->next)
			current = current->next;
		printf("Value found between indexes [%lu] and [%lu]\n",
			   current->index, current->index);
	}
	else
	{
		printf("Value found between indexes [%lu] and [%lu]\n",
			   current->index, express_node->index);
	}

	while (current)
	{
		printf("Value checked at index [%lu] = [%d]\n",
			   current->index, current->n);
		if (current->n == value)
			return (current);
		current = current->next;
	}

	return (NULL);
}
