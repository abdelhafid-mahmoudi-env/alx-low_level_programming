#include <stdio.h>
#include <stdlib.h>

/**
 * malloc_checked - Allocates memory using malloc
 * @b: The number of bytes to allocate
 *
 * Return: A pointer to the allocated memory
 * If malloc fails, the function terminates with status 98.
 */
void *malloc_checked(unsigned int b)
{
	/* Use tabs for indentation here */
	void *ptr;

	ptr = malloc(b);
	if (ptr == NULL)
	{
		exit(98);  /* Terminate the process with status 98 */
	}

	return (ptr);
}
