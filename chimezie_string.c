#include "chimezie_shell.h"

/**
 * _strlen - A function that returns the length of a string
 * @string: the string whose length to check
 *
 * Return: The integer length of string
 */
int _strlen(char *string)
{
	int n = 0;

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
 * starts_with - A function that checks if needle starts with haystack
 * @hayStack: the string to search
 * @ndle: substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *hayStack, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hayStack++)
			return (NULL);
	return ((char *)hayStack);
}

/**
 * _strcat - A function that concatenates two strings
 * @destn: The destination buffer
 * @src: The source buffer
 *
 * Return: A pointer to destination buffer
 */
char *_strcat(char *destn, char *src)
{
	char *res = destn;

	while (*destn)
		destn++;
	while (*src)
		*destn++ = *src++;
	*destn = *src;
	return (res);
}
