#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_tables.h"

/**
 * shash_table_create - Create a sorted hash table
 * @size: The size of the array
 *
 * Return: A pointer to the created hash table, or NULL if it fails
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht = malloc(sizeof(shash_table_t));

	if (!ht)
		return (NULL);

	ht->size = size;
	ht->array = calloc(size, sizeof(shash_node_t *));
	if (!ht->array)
	{
		free(ht);
		return (NULL);
	}

	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - Add a key/value pair to the sorted hash table
 * @ht: The sorted hash table
 * @key: The key
 * @value: The value associated with the key
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new_node, *current;

	if (!ht || !key || *key == '\0' || !value)
		return (0);

	new_node = malloc(sizeof(shash_node_t));
	if (!new_node)
		return (0);

	new_node->key = strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (0);
	}
	new_node->value = strdup(value);
	if (!new_node->value)
	{
		free(new_node->key);
		free(new_node);
		return (0);
	}
	new_node->next = NULL;

	if (!ht->shead)
	{
		ht->shead = new_node;
		ht->stail = new_node;
	}
	else if (strcmp(key, ht->shead->key) < 0)
	{
		new_node->next = ht->shead;
		ht->shead->sprev = new_node;
		ht->shead = new_node;
	}
	else
	{
		current = ht->shead;
		while (current->next && strcmp(key, current->next->key) >= 0)
			current = current->next;

		new_node->next = current->next;
		if (current->next)
			current->next->sprev = new_node;
		else
			ht->stail = new_node;
		current->next = new_node;
		new_node->sprev = current;
	}
	/* Handle collisions in the regular hash table */
	new_node->next = ht->array[key_index((unsigned char *)key, ht->size)];
	ht->array[key_index((unsigned char *)key, ht->size)] = new_node;

	return (1);
}

/**
 * shash_table_get - Retrieve a value associated with a key
 * @ht: The sorted hash table
 * @key: The key to search for
 *
 * Return: The value associated with the key, or NULL if the key is not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *node;

	if (!ht || !key || *key == '\0')
		return (NULL);

	node = ht->array[key_index((unsigned char *)key, ht->size)];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}

	return (NULL);
}

/**
 * shash_table_print - Print the sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	int first = 1;
	shash_node_t *node;

	if (!ht)
		return;

	printf("{");
	node = ht->shead;
	while (node)
	{
		if (first)
			first = 0;
		else
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		node = node->next;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Print the sorted hash table in reverse order
 * @ht: The sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	int first = 1;
	shash_node_t *node;

	if (!ht)
		return;

	printf("{");
	node = ht->stail;
	while (node)
	{
		if (first)
			first = 0;
		else
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Delete the sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node, *temp;

	if (!ht)
		return;

	node = ht->shead;
	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}

	free(ht->array);
	free(ht);
}
