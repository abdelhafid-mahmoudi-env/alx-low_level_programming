#include "dog.h"

/**
 * free_dog - Frees dog
 * @d: dog to be freed
 *
 * Description: This function frees memory allocated for a dog structure.
 */
void free_dog(dog_t *d)
{
	if (d == NULL)
		return;

	free(d->name);
	free(d->owner);
	free(d);
}
