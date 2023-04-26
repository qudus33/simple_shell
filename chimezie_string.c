#include "chimezie_shell.h"

/**
 * _strlen - A function that returns the length of a string
 * @string: the string whose length to check
 *
 * Return: The integer length of string
 */
int _strlen(char *string)
{
	intni = 0;

	if (!string)
		return (0);

	while (*string++)
		n++;
	return (n);
}

/**
 * _strcmp - A function that performs lexicogarphic comparison of two strings.
 * @string1: The first string
 * @string2: The second string
 *
 * Return: Negative if string1 < string2, positive if
 * string1 > string2, zero if string1 == string2
 */
int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * begin_with - A function that checks if needle starts with haystack
 * @hstack: string to search
 * @nidle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *begin_with(const char *hstack, const char *nidle)
{
	while (*nidle)
		if (*nidle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * _strcat - A function that concatenates two strings
 * @destin: The destination buffer
 * @sorc: The source buffer
 *
 * Return: A pointer to destination buffer
 */
char *_strcat(char *destin, char *sorc)
{
	char *res = destin;

	while (*destin)
		destin++;
	while (*sorc)
		*destin++ = *sorc++;
	*destin = *sorc;
	return (res);
}
