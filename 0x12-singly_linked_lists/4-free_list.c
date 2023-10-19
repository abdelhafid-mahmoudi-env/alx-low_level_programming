#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * free_list - Frees a singly linked list and its string contents.
 * @head: A pointer to the head of the list.
 *
 * This function iterates through the list and frees each node and its
 * associated string content.
 */
void free_list(list_t *head)
{
	list_t *current_node, *next_node;

	if (head == NULL)
		return;

	current_node = head;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
}
