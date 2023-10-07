#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * _memset - initializes n bytes of memory to x
 * @ptr: initial address
 * @x: variable to initialize with
 * @n: number of bytes to initialize
 *
 * Return: Return pointer char (so movements are 1 byte)
 */
char *_memset(char *ptr, int x, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		ptr[i] = x;
	return (ptr);
}

/**
 * _calloc - allocates memory using malloc and initializes to 0
 * @nmemb: number of elements of array to allocate
 * @size: size of elements
 *
 * Return: Pointer to allocated memory or NULL on failure
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *p;

	if (nmemb == 0 || size == 0)
		return (NULL);

	p = malloc(nmemb * size);

	if (p == NULL)
		return (NULL);

	_memset(p, 0, nmemb * size);

	return (p);
}

