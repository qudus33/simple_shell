#include "shell.h"

/**
 * bfree - A function that frees a pointer and NULLs the address
 * @ptar: The address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptar)
{
	if (ptar && *ptar)
	{
		free(*ptar);
		*ptar = NULL;
		return (1);
	}
	return (0);
}
