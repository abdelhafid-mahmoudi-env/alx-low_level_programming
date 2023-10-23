#include "lists.h"
#include <stdlib.h>

/**
 * free_listint_safe - Frees a listint_t list safely (can free lists containing loops)
 * @h: A pointer to the address of the head of the listint_t list.
 *
 * Return: The size of the list that was freed.
 */
size_t free_listint_safe(listint_t **h)
{
    listint_t *slow, *fast, *tmp;
    size_t count = 0;

    if (h == NULL || *h == NULL)
        return (0);

    slow = *h;
    fast = (*h)->next;

    while (fast && fast->next)
    {
        if (slow == fast)
        {
            /* Detected a loop, break it */
            slow = *h;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
                count++;
            }

            slow = fast->next;
            while (slow != fast)
            {
                tmp = slow;
                slow = slow->next;
                free(tmp);
                count++;
            }

            tmp = slow;
            slow = slow->next;
            free(tmp);
            count++;
            *h = NULL;
            break;
        }

        slow = slow->next;
        fast = fast->next->next;
    }

    if (!fast || !fast->next)
    {
        while (*h)
        {
            tmp = *h;
            *h = (*h)->next;
            free(tmp);
            count++;
        }
    }

    h = NULL;

    return (count);
}
