#include "hash_tables.h"

/**
 * key_index - Gives the index of a key in the hash table.
 * @key: The key to find the index for.
 * @size: The size of the array of the hash table.
 *
 * Return: The index at which the key/value pair should be stored.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int hash;

	/* Use the djb2 algorithm to get the hash value for the key */
	hash = hash_djb2(key);

	/* Use modulo operation to get an index within the bounds of the array */
	return (hash % size);
}
