#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * print_list - Print all elements of a list_t list.
 * @h: A pointer to the beginning of the list.
 *
 * Return: The number of nodes.
 */
size_t print_list(const list_t *h)
{
    size_t count = 0;

    while (h)
    {
        if (h->str)
            printf("[%u] %s\n", h->len, h->str);
        else
            printf("[0] (nil)\n");

        h = h->next;
        count++;
    }

    return (count);
}
