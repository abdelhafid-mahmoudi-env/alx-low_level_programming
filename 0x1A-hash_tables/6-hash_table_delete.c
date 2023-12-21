#include "hash_tables.h"

/**
 * hash_table_delete - Deletes a hash table.
 * @ht: The hash table to be deleted.
 */
void hash_table_delete(hash_table_t *ht)
{
	unsigned long int i;
	hash_node_t *node, *temp;

	if (ht == NULL)
		return;

	/* Iterate over each index in the array */
	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		/* Free each node in the linked list */
		while (node != NULL)
		{
			temp = node;
			node = node->next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
	}

	/* Free the array and the hash table itself */
	free(ht->array);
	free(ht);
}
