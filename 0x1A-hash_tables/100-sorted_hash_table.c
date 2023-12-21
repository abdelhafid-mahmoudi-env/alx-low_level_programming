#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the hash table
 *
 * Return: A pointer to the created sorted hash table.
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht = NULL;
	unsigned long int i = 0;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);
	ht->size = size;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}
	for (i = 0; i < size; i++)
		ht->array[i] = NULL;
	ht->shead = NULL;
	ht->stail = NULL;
	return (ht);
}

/**
 * shash_table_set - Adds an element to the sorted hash table
 * @ht: The sorted hash table to add or update the key/value in
 * @key: The key to add (or update)
 * @value: The value associated with the key
 *
 * Return: 1 if successful, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *new_node = NULL, *temp = NULL;

	if (ht == NULL || key == NULL || value == NULL || strcmp(key, "") == 0)
		return (0);
	index = key_index((unsigned char *)key, ht->size);
	temp = ht->array[index];
	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = strdup(value);
			if (temp->value == NULL)
				return (0);
			return (1);
		}
		temp = temp->next;
	}
	new_node = malloc(sizeof(shash_node_t));
	if (new_node == NULL)
		return (0);
	new_node->key = strdup(key);
	if (new_node->key == NULL)
	{
		free(new_node);
		return (0);
	}
	new_node->value = strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node);
		return (0);
	}
	new_node->next = ht->array[index];
	ht->array[index] = new_node;
	if (insert_sorted_node(ht, new_node) == 0)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (0);
	}
	return (1);
}

/**
 * shash_table_get - Retrieves a value associated.
 * @ht: The sorted hash table to search
 * @key: The key to search for
 *
 * Return: The value associated.
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *temp = NULL;

	if (ht == NULL || key == NULL || strcmp(key, "") == 0)
		return (NULL);
	index = key_index((unsigned char *)key, ht->size);
	temp = ht->array[index];
	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * shash_table_print - Prints the sorted hash table
 * @ht: The sorted hash table to print
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node = NULL;
	int flag = 0;

	if (ht == NULL)
		return;
	node = ht->shead;
	putchar('{');
	while (node != NULL)
	{
		if (flag == 1)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		flag = 1;
		node = node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints the sorted hash table in reverse
 * @ht: The sorted hash table to print
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node = NULL;
	int flag = 0;

	if (ht == NULL)
		return;
	node = ht->stail;
	putchar('{');
	while (node != NULL)
	{
		if (flag == 1)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		flag = 1;
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes the sorted hash table
 * @ht: The sorted hash table to delete
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *current_node = NULL, *next_node = NULL;
	unsigned long int i;

	if (ht == NULL)
		return;
	for (i = 0; i < ht->size; i++)
	{
		current_node = ht->array[i];
		while (current_node != NULL)
		{
			next_node = current_node->next;
			free(current_node->key);
			free(current_node->value);
			free(current_node);
			current_node = next_node;
		}
	}
	free(ht->array);
	free(ht);
}

/**
 * insert_sorted_node - Inserts a node into the sorted.
 * @ht: The sorted hash table
 * @new_node: The new node to insert
 *
 * Return: 1 if successful, 0 on failure
 */
int insert_sorted_node(shash_table_t *ht, shash_node_t *new_node)
{
	shash_node_t *current_node = NULL;

	if (ht == NULL || new_node == NULL)
		return (0);
	if (ht->shead == NULL || strcmp(new_node->key, ht->shead->key) <= 0)
	{
		new_node->snext = ht->shead;
		ht->shead = new_node;
		if (ht->stail == NULL)
			ht->stail = new_node;
		return (1);
	}
	current_node = ht->shead;
	while (current_node->snext != NULL &&
	       strcmp(new_node->key, current_node->snext->key) > 0)
		current_node = current_node->snext;
	new_node->snext = current_node->snext;
	new_node->sprev = current_node;
	if (current_node->snext != NULL)
		current_node->snext->sprev = new_node;
	current_node->snext = new_node;
	if (new_node->snext == NULL)
		ht->stail = new_node;
	return (1);
}
