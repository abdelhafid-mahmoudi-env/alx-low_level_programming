#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * insert_nodeint_at_index - Inserts a new node
 * at a given position in a listint_t list.
 * @head: A pointer to a pointer to the head of the list.
 * @idx: The index at which to insert the new node (starting at 0).
 * @n: The integer value to store in the new node.
 *
 * Return: The address of the new node, or NULL if it fails.
 */
listint_t *insert_nodeint_at_index(listint_t **head, unsigned int idx, int n)
{
	listint_t *new_node, *current = *head;
	unsigned int i;

	if (idx == 0)
	{
		new_node = add_nodeint(head, n);
		return (new_node);
	}

	for (i = 0; i < idx - 1; i++)
	{
		if (current == NULL)
			return (NULL);
		current = current->next;
	}

	if (current == NULL)
		return (NULL);

	new_node = add_nodeint(&(current->next), n);
	return (new_node);
}
