#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

/**
 * create_node - Creates a new node with a duplicated string and length.
 *
 * @str: The string to be duplicated.
 * @len: The length of the string.
 * Return: A pointer to the newly created node.
 */
list_t *create_node(const char *str, size_t len)
{
    list_t *new_node = malloc(sizeof(list_t));

    if (new_node == NULL)
        return (NULL);

    new_node->len = len;
    new_node->str = strdup(str);

    if (new_node->str == NULL)
    {
        free(new_node);
        return (NULL);
    }

    new_node->next = NULL;

    return (new_node);
}

/**
 * add_node - Adds a new node at the beginning of a singly linked list.
 *
 * @head: A pointer to the pointer of the linked list.
 * @str: The string to be added to the list.
 * Return: A pointer to the newly created node or NULL if it fails.
 */
list_t *add_node(list_t **head, const char *str)
{
    size_t length = 0;
    list_t *new_node;

    while (str[length])
        length++;

    new_node = create_node(str, length);

    if (new_node == NULL)
        return (NULL);

    new_node->next = *head;
    *head = new_node;

    return (new_node);
}

