#include "chimezie_shell.h"

/**
 * gfree - A function that frees a pointer and NULLs the address
 * @ptr: The address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int gfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
