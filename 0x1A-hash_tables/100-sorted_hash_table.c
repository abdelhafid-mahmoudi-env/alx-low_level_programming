#include "hash_tables.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the array
 *
 * Return: A pointer to the created sorted hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *new_ht = NULL;
	unsigned long int i = 0;

	new_ht = malloc(sizeof(shash_table_t));
	if (new_ht == NULL)
		return (NULL);

	new_ht->size = size;
	new_ht->array = malloc(sizeof(shash_node_t *) * size);
	if (new_ht->array == NULL)
	{
		free(new_ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		new_ht->array[i] = NULL;

	new_ht->shead = NULL;
	new_ht->stail = NULL;

	return (new_ht);
}

/**
 * shash_table_set - Adds an element to the sorted hash table
 * @ht: The sorted hash table
 * @key: The key
 * @value: The value associated with the key
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new_node = NULL, *current = NULL;

	if (ht == NULL || key == NULL || value == NULL)
		return (0);

	new_node = malloc(sizeof(shash_node_t));
	if (new_node == NULL)
		return (0);

	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = NULL;
	new_node->sprev = NULL;
	new_node->snext = NULL;

	if (new_node->key == NULL || new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (0);
	}

	if (ht->shead == NULL)
	{
		ht->shead = new_node;
		ht->stail = new_node;
	}
	else if (strcmp(new_node->key, ht->shead->key) < 0)
	{
		new_node->snext = ht->shead;
		ht->shead->sprev = new_node;
		ht->shead = new_node;
	}
	else
	{
		current = ht->shead;
		while (current->snext != NULL && strcmp(new_node->key, current->snext->key) > 0)
			current = current->snext;

		new_node->snext = current->snext;
		if (current->snext != NULL)
			current->snext->sprev = new_node;
		new_node->sprev = current;
		current->snext = new_node;

		if (new_node->snext == NULL)
			ht->stail = new_node;
	}

	if (key_index((unsigned char *)key, ht->size) == 0)
	{
		if (ht->array[key_index((unsigned char *)key, ht->size)] == NULL)
			ht->array[key_index((unsigned char *)key, ht->size)] = new_node;
		else
		{
			current = ht->array[key_index((unsigned char *)key, ht->size)];
			while (current != NULL)
			{
				if (strcmp(current->key, key) == 0)
				{
					free(current->value);
					current->value = strdup(value);
					free(new_node->key);
					free(new_node->value);
					free(new_node);
					return (1);
				}
				current = current->next;
			}
			new_node->next = ht->array[key_index((unsigned char *)key, ht->size)];
			ht->array[key_index((unsigned char *)key, ht->size)] = new_node;
		}
	}
	else
	{
		if (ht->array[key_index((unsigned char *)key, ht->size)] == NULL)
			ht->array[key_index((unsigned char *)key, ht->size)] = new_node;
		else
		{
			current = ht->array[key_index((unsigned char *)key, ht->size)];
			while (current != NULL)
			{
				if (strcmp(current->key, key) == 0)
				{
					free(current->value);
					current->value = strdup(value);
					free(new_node->key);
					free(new_node->value);
					free(new_node);
					return (1);
				}
				current = current->next;
			}
			new_node->next = ht->array[key_index((unsigned char *)key, ht->size)];
			ht->array[key_index((unsigned char *)key, ht->size)] = new_node;
		}
	}

	return (1);
}

/**
 * shash_table_get - Retrieves the value associated with a key
 * @ht: The sorted hash table
 * @key: The key to search for
 *
 * Return: The value associated with the key, or NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index = 0;
	shash_node_t *current = NULL;

	if (ht == NULL || key == NULL)
		return (NULL);

	index = key_index((unsigned char *)key, ht->size);
	if (index >= ht->size || ht->array[index] == NULL)
		return (NULL);

	current = ht->array[index];
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}

	return (NULL);
}

/**
 * shash_table_print - Prints the sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *current = NULL;
	int first = 1;

	if (ht == NULL)
		return;

	current = ht->shead;
	printf("{");
	while (current != NULL)
	{
		if (!first)
			printf(", ");
		printf("'%s': '%s'", current->key, current->value);
		first = 0;
		current = current->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints the sorted hash table in reverse
 * @ht: The sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *current = NULL;
	int first = 1;

	if (ht == NULL)
		return;

	current = ht->stail;
	printf("{");
	while (current != NULL)
	{
		if (!first)
			printf(", ");
		printf("'%s': '%s'", current->key, current->value);
		first = 0;
		current = current->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes the sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *current = NULL, *temp = NULL;

	if (ht == NULL)
		return;

	current = ht->shead;
	while (current != NULL)
	{
		temp = current;
		current = current->snext;
		free(temp->key);
		free(temp->value);
		free(temp);
	}

	free(ht->array);
	free(ht);
}
