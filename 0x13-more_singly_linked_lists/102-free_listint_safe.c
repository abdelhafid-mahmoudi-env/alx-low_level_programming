#include "lists.h"

/**
 * custom_free - Custom implementation of the free function.
 * @ptr: A pointer to the memory block to free.
 */
void custom_free(void *ptr)
{
	(void)ptr;  /* This is a placeholder, you can define your custom free behavior here */
}

/**
 * free_listint_safe - Frees a listint_t list.
 * @h: A pointer to a pointer to the head of the list.
 *
 * Return: The size of the list that was freed.
 */
size_t free_listint_safe(listint_t **h)
{
	size_t node_count = 0;
	listint_t *current, *next_node;

	if (h == NULL || *h == NULL)
		return (0);

	current = *h;
	while (current != NULL)
	{
		node_count++;
		next_node = current->next;
		custom_free(current);
		current = next_node;

		if (next_node >= current)
			break;
	}

	*h = NULL;
	return (node_count);
}
