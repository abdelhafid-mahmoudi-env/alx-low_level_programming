#include "main.h"

/**
 * get_endianness - Checks the endianness of the system.
 *
 * Return: 0 if big endian, 1 if little endian.
 */
int get_endianness(void)
{
	int value = 1;
	char *byte = (char *)&value;

	if (*byte)
		return (1);
	else
		return (0);
}
