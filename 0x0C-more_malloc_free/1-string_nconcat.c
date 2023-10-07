#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - function that concatenates two strings with s2 by n amount.
 * @s1: base string to concatenate to. NULL will be treated as an empty string.
 * @s2: string to copy from. NULL will be treated as an empty string.
 * @n: amount of s2 to copy.
 * Return: pointer to allocated memory.
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *str;
	unsigned int len1 = 0, len2 = 0, i, j;

	/* Calculate the length of s1 */
	if (s1)
		for (; s1[len1]; len1++)
			;

	/* Calculate the length of s2 */
	if (s2)
		for (; s2[len2]; len2++)
			;

	/* Adjust n if it's greater than or equal to the length of s2 */
	if (!(n >= len2))
		len2 = n;

	/* Allocate memory for the concatenated string (including null terminator) */
	str = malloc(sizeof(char) * (len1 + len2 + 1));

	if (!str)
		return (NULL);

	/* Copy characters from s1 and s2 to str */
	for (i = 0; i < len1; i++)
		str[i] = s1[i];
	for (j = 0; j < len2; j++, i++)
		str[i] = s2[j];

	str[i] = '\0';

	return (str);
}

