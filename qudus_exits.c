#include "chimezie_shell.h"

/**
 **_strncpy - string copy
 *@dest: destination string to be copied
 *@src: source string to copy
 *@n: no of characters to be copied
 *Return: returns the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int p, q;
	char *s = dest;

	p = 0;
	while (src[p] != '\0' && p < n - 1)
	{
		dest[p] = src[p];
		p++;
	}
	if (p < n)
	{
		q = p;
		while (q < n)
		{
			dest[q] = '\0';
			q++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates 2 strings
 *@dest: destination string
 *@src: source string
 *@n: no of bytes to be maximally used
 *Return: returns the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int p, q;
	char *s = dest;

	p = 0;
	q = 0;
	while (dest[p] != '\0')
		p++;
	while (src[q] != '\0' && q < n)
	{
		dest[p] = src[q];
		p++;
		q++;
	}
	if (q < n)
		dest[p] = '\0';
	return (s);
}

/**
 **_strchr - gets a char in a string
 *@s: string to be checked
 *@c: char to check for
 *Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
