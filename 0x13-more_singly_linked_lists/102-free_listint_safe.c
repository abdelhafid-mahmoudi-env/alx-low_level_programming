#include "lists.h"
#include <stdlib.h>

/**
 * free_listint_safe - Frees a listint_t linked list safely.
 * @h: A pointer to a pointer to the head of the list.
 *
 * Return: The size of the list that was freed.
 */
size_t free_listint_safe(listint_t **h)
{
    listint_t *slow, *fast, *temp;
    size_t count = 0;

    slow = fast = *h;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            while (*h != slow)
            {
                temp = *h;
                *h = (*h)->next;
                free(temp);
                count++;
            }

            *h = NULL;
            return (count);
        }
    }

    while (*h != NULL)
    {
        temp = *h;
        *h = (*h)->next;
        free(temp);
        count++;
    }

    return (count);
}
