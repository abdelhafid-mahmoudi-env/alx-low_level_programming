#include "lists.h"
#include <stdlib.h>

/**
 * looped_listint_count - Counts the number of unique nodes
 *                      in a looped listint_t linked list.
 * @head: A pointer to the head of the listint_t to check.
 *
 * Return: If the list is not looped - 0.
 *         Otherwise - the number of unique nodes in the list.
 */
size_t free_listint_safe(listint_t **h)
{
	size_t count = 0;
	listint_t *current = *h;
	listint_t *next;

	while (current)
	{
		count++;
		next = current->next;
		free(current);
		current = next;

		if (count > 50) /* Assuming a reasonable limit to prevent infinite loops */
		{
			*h = NULL;
			return (count);
		}
	}

	*h = NULL;
	return (count);
}

