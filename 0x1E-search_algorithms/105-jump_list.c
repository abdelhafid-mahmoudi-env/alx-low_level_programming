#include "search_algos.h"

/**
 * jump_list - jump searches on singly linked list
 * @list: pointer to head node
 * @size: its size
 * @value: value to search for
 *
 * Return: the node found or NULL
 */
listint_t *jump_list(listint_t *list, size_t size, int value)
{
	size_t index = 0, jump_size = sqrt(size), count = 0, last_jump_index = 0;
	listint_t *last_node = list;

	if (!list)
		return (NULL);

	while (list->n < value)
	{
		for (last_jump_index = index, last_node = list, count = 0; list->next && count < jump_size; count++)
		{
			list = list->next;
			index++;
		}
		printf("Value checked at index [%lu] = [%d]\n", index, list->n);
		if (!list->next)
			break;
	}

	if (!list->next)
		jump_size = last_jump_index;
	else
		jump_size = index >= jump_size ? index - jump_size : 0;
	printf("Value found between indexes [%lu] and [%lu]\n", jump_size, index);
	index = index >= size ? size - 1 : index;
	list = last_node;
	while (list)
	{
		printf("Value checked at index [%lu] = [%d]\n", jump_size, list->n);
		if (list->n == value)
			return (list);
		jump_size++;
		list = list->next;
	}
	return (NULL);
}
