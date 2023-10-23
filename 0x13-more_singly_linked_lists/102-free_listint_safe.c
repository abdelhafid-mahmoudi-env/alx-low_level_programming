#include "lists.h"

size_t free_listint_safe(listint_t **h)
{
    listint_t *slow, *fast, *temp;
    size_t size = 0;

    if (h == NULL || *h == NULL)
        return (0);

    slow = *h;
    fast = (*h)->next;

    while (fast != NULL && fast->next != NULL)
    {
        if (slow == fast)
        {
            /* Loop detected, free the entire list and break */
            slow = *h;
            while (slow != fast)
            {
                temp = slow;
                slow = slow->next;
                free(temp);
                size++;
            }
            *h = NULL; /* Set the head to NULL */
            return (size);
        }
        slow = slow->next;
        fast = fast->next->next;
        size++;
    }

    /* No loop detected, free the list normally */
    while (*h != NULL)
    {
        temp = *h;
        *h = (*h)->next;
        free(temp);
        size++;
    }

    return (size);
}

