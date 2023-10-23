#include "lists.h"
#include <stdlib.h>

listint_t *find_listint_loop(listint_t *head)
{
    listint_t *slow = head, *fast = head;

    while (slow && fast && fast->next)
    {
        slow = slow->next;           // Move one step at a time
        fast = fast->next->next;     // Move two steps at a time

        if (slow == fast)
        {
            // There is a loop, reset one of the pointers and find the start of the loop
            slow = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;  // Return the start of the loop
        }
    }

    return NULL;  // No loop found
}

