#include "variadic_functions.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * print_strings - prints strings separated by a separator
 * @separator: string to separate the strings
 * @n: number of elements to print
 * @...: variable number of strings to print
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
	va_list vls;
	unsigned int i;
	char *r;

	va_start(vls, n);
	i = 0;

	while (i < n)
	{
		r = va_arg(vls, char *);
		if (!r)
			printf("(nil)");
		else
			printf("%s", r);

		i++;
		if (i < n && separator)
			printf("%s", separator);
	}

	putchar('\n');
	va_end(vls);
}

