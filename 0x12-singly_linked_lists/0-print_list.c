#include <stdio.h>
#include "lists.h"

void print_node(const list_t *node);

/**
 * print_list - Print all elements in a singly linked list and return the count.
 *
 * @h: Head of the list
 * Return: Total number of nodes in the list
 */
size_t print_list(const list_t *h)
{
    size_t count = 0;  /* Initialize a count variable to keep track of nodes. */

    if (h == NULL) {
        return 0; /* Handle the case of an empty list by returning 0. */
    }

    while (h != NULL) {
        print_node(h);  /* Print the current node. */
        h = h->next;    /* Move to the next node. */
        count++;        /* Increment the count for each node processed. */
    }

    return count; /* Return the total count of nodes in the list. */
}

/**
 * print_node - Print a single node from the singly linked list.
 *
 * @node: Node to be printed
 */
void print_node(const list_t *node)
{
    /* Print the length and the string (or "(nil)" for NULL strings). */
    if (node->str == NULL) {
        printf("[%u] %s\n", 0, "(nil)");
    } else {
        printf("[%u] %s\n", node->len, node->str);
    }
}
