#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * print_list - function that prints all the elements of a list_t.
 * @h: pointer to the list.
 *
 * if str is NULL print [0] (nil).
 * You are allowed to use printf.
 *
 * Return: the number of nodes.
 */
size_t print_list(const list_t *h)
{
    size_t count = 0;

    while (h != NULL)
    {
        if (h->str == NULL)
        {
            printf("[%lu] %s\n", (unsigned long)count, "(nil)");
        }
        else
        {
            printf("[%lu] %s\n", (unsigned long)h->len, h->str);
        }
        h = h->next;
        count++;
    }
    return (count);
}

