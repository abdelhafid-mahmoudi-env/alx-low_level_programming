#include <stdio.h>
#include "lists.h"


/**
 * print_list - Prints elements of a singly linked list and returns the count.
 *
 * @h: The head of the list
 *
 * Return: The total number of nodes in the list
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	if (h == NULL)
	{
		return (0);
	}

	while (h != NULL)
	{
		if (h->str == NULL)
		{
			printf("[%u] %s\n", 0, "(nil)");
		}
		else
		{
			printf("[%u] %s\n", h->len, h->str);
		}
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * print_node - Prints a single node from the singly linked list.
 *
 * @node: The node to be printed
 */
void print_node(const list_t *node)
{
	if (node->str == NULL)
	{
		printf("[%u] %s\n", 0, "(nil)");
	}
	else
	{
		printf("[%u] %s\n", node->len, node->str);
	}
}

