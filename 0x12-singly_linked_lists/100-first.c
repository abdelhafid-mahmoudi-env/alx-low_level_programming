#include "lists.h"

void weird(void) __attribute__ ((constructor));

/**
 * weird - This function is executed before main.
 *
 * It prints the desired message.
 */
void weird(void)
{
    printf("You're beat! and yet, you must allow,\n"
           "I bore my house upon my back!\n");
}
