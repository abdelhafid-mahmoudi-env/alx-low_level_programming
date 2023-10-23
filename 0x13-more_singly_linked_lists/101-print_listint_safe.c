#include "lists.h"
#include <stdio.h>

/**
 * print_listint_safe - Prints a listint_t list safely.
 * @head: A pointer to the head of the listint_t list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_listint_safe(const listint_t *head)
{
    size_t node_count = 0;
    const listint_t *current = head;
    const listint_t *loop_node = NULL;

    while (current)
    {
        node_count++;
        printf("[%p] %d\n", (void *)current, current->n);

        if (current == current->next)
        {
            loop_node = current;
            break;
        }

        current = current->next;

        if (node_count > 2 && current == loop_node)
            break;
    }

    if (loop_node)
        printf("-> [%p] %d\n", (void *)current, current->n);

    return node_count;
}
