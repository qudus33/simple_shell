#include "shell.h"

/**
 * _strcpy - A function that copies a string
 * @destin: The destination
 * @sorc: the source
 *
 * Return: A pointer to destination
 */
char *_strcpy(char *destin, char *sorc)
{
	int n = 0;

	if (destin == sorc || sorc == 0)
		return (destin);
	while (sorc[n])
	{
		destin[n] = sorc[n];
		n++;
	}
	destin[n] = 0;
	return (destin);
}

/**
 * _strdup - A function thatduplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int lent = 0;
	char *res;

	if (string == NULL)
		return (NULL);
	while (*string++)
		lent++;
	res = malloc(sizeof(char) * (lent + 1));
	if (!res)
		return (NULL);
	for (lent++; lent--;)
		res[lent] = *--string;
	return (res);
}

/**
 *_puts - A function that prints an input string
 *@string: The string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int n = 0;

	if (!string)
		return;
	while (string[n] != '\0')
	{
		_putchar(string[n]);
		n++;
	}
}

/**
 * _putchar - A function that writes the character c to stdout
 * @s: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char s)
{
	static int n;
	static char buffa[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buffa, n);
		n = 0;
	}
	if (s != BUF_FLUSH)
		buffa[n++] = s;
	return (1);
}
