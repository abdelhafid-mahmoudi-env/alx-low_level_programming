#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_numbers - prints numbers separated by a separator
 * @separator: string to separate the numbers
 * @n: number of elements to print
 * @...: variable number of arguments to print
 */
void print_numbers(const char *separator, const unsigned int n, ...)
{
	va_list vls;
	unsigned int i = 0;

	va_start(vls, n);

	while (i < n)
	{
		printf("%d", va_arg(vls, int));
		i++;

		if (i < n && separator)
			printf("%s", separator);
	}

	putchar('\n');
	va_end(vls);
}
