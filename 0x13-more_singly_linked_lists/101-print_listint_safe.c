#include "lists.h"
#include <stdio.h>

/**
 * map_len - Counts the number of unique nodes
 *           in a looped listint_t linked list.
 * @h: A pointer to the head of the listint_t to check.
 *
 * Return: If the list is not looped - 0.
 *         Otherwise - the number of unique nodes in the list.
 */
size_t map_len(const listint_t *h)
{
	const listint_t *slow, *fast;
	size_t count = 1;

	if (h == NULL || h->next == NULL)
		return (0);

	slow = h->next;
	fast = (h->next)->next;

	while (fast)
	{
		if (slow == fast)
		{
			slow = h;
			while (slow != fast)
			{
				count++;
				slow = slow->next;
				fast = fast->next;
			}

			slow = slow->next;
			while (slow != fast)
			{
				count++;
				slow = slow->next;
			}

			return (count);
		}

		slow = slow->next;
		fast = (fast->next)->next;
	}

	return (0);
}

/**
 * print_listint_safe - Prints a listint_t list safely.
 * @head: A pointer to the head of the listint_t list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_listint_safe(const listint_t *head)
{
	size_t num_nodes, index = 0;

	num_nodes = map_len(head);

	if (num_nodes == 0)
	{
		for (; head != NULL; num_nodes++)
		{
			printf("[%p] %d\n", (void *)head, head->n);
			head = head->next;
		}
	}
	else
	{
		for (index = 0; index < num_nodes; index++)
		{
			printf("[%p] %d\n", (void *)head, head->n);
			head = head->next;
		}

		printf("-> [%p] %d\n", (void *)head, head->n);
	}

	return (num_nodes);
}
