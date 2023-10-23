#include <stdlib.h>
#include "lists.h"

size_t random_function_name(listint_t *random_head_name);
size_t free_listint_safe(listint_t **h);

/**
 * random_function_name - Counts the number of unique nodes
 *                      in a looped listint_t linked list.
 * @random_head_name: A pointer to the head of the listint_t to check.
 *
 * Return: If the list is not looped - 0.
 *         Otherwise - the number of unique nodes in the list.
 */
size_t random_function_name(listint_t *random_head_name)
{
	listint_t *random_tortoise, *random_hare;
	size_t random_nodes = 1;

	if (random_head_name == NULL || random_head_name->next == NULL)
		return (0);

	random_tortoise = random_head_name->next;
	random_hare = (random_head_name->next)->next;

	while (random_hare)
	{
		if (random_tortoise == random_hare)
		{
			random_tortoise = random_head_name;
			while (random_tortoise != random_hare)
			{
				random_nodes++;
				random_tortoise = random_tortoise->next;
				random_hare = random_hare->next;
			}

			random_tortoise = random_tortoise->next;
			while (random_tortoise != random_hare)
			{
				random_nodes++;
				random_tortoise = random_tortoise->next;
			}

			return (random_nodes);
		}

		random_tortoise = random_tortoise->next;
		random_hare = (random_hare->next)->next;
	}

	return (0);
}

/**
 * free_listint_safe - Frees a listint_t list safely (i.e.
 *                     can free lists containing loops)
 * @h: A pointer to the address of
 *     the head of the listint_t list.
 *
 * Return: The size of the list that was freed.
 */
size_t free_listint_safe(listint_t **h)
{
	listint_t *random_tmp;
	size_t random_nodes, random_index;

	random_nodes = random_function_name(*h);

	if (random_nodes == 0)
	{
		for (; h != NULL && *h != NULL; random_nodes++)
		{
			random_tmp = (*h)->next;
			free(*h);
			*h = random_tmp;
		}
	}
	else
	{
		for (random_index = 0; random_index < random_nodes; random_index++)
		{
			random_tmp = (*h)->next;
			free(*h);
			*h = random_tmp;
		}

		*h = NULL;
	}

	h = NULL;

	return (random_nodes);
}
