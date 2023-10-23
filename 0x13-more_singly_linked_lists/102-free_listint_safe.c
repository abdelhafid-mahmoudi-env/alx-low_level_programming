#include "lists.h"

/**
 * free_listint_safe - Frees a listint_t list safely.
 * @h: A pointer to the address of the head of the listint_t list.
 *
 * Return: The size of the list that was freed.
 *
 * Description: This function sets the head to NULL.
 */
size_t free_listint_safe(listint_t **h)
{
	listint_t *current, *next;
	size_t nodes = 0;

	if (h == NULL || *h == NULL)
		return (0);

	while (*h != NULL)
	{
		current = *h;
		next = current->next;
		*h = NULL;
		free(current);
		*h = next;
		nodes++;
	}

	return (nodes);
}
