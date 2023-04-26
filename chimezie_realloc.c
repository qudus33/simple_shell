#include "chimezie_shell.h"

/**
 **_memset - A function fills memory with a constant byte
 *@m: the pointer to the memory area
 *@b: the byte to fill *m with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *m, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		m[j] = b;
	return (m);
}

/**
 * ffree - A function frees a string of strings
 * @sos: string of strings
 */
void ffree(char **sos)
{
	char **b = sos;

	if (!sos)
		return;
	while (*sos)
		free(*sos++);
	free(b);
}

/**
 * _realloc - A function that reallocates a block of memory
 * @ptar: pointer to previous malloc'ated block
 * @pre_size: byte size of previous block
 * @lat_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptar, unsigned int pre_size, unsigned int lat_size)
{
	char *q;

	if (!ptar)
		return (malloc(lat_size));
	if (!lat_size)
		return (free(ptar), NULL);
	if (lat_size == pre_size)
		return (ptr);

	q = malloc(lat_size);
	if (!q)
		return (NULL);

	pre_size = pre_size < lat_size ? pre_size : lat_size;
	while (lat_size--)
		q[pre_size] = ((char *)ptar)[pre_size];
	free(ptar);
	return (q);
}
