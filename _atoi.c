#include "shell.h"

/**
 * interactive - true if shell is interactive mode
 * @info: struct address
 *
 * Return: returns 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - character delimeter checker
 * @c: char to check
 * @delim: delimeter string
 * Return: returns 1 if true, 0 if false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - alphabetic character check
 *@c: character to input
 *Return: returns 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts string to integer
 *@s: string to be converted
 *Return: returns 0 if no numbers in string,
 * converted number otherwise
 */

int _atoi(char *s)
{
	int i, my_sign = 1, flags = 0, result;
	unsigned int output = 0;

	for (i = 0;  s[i] != '\0' && flags != 2; i++)
	{
		if (s[i] == '-')
			my_sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flags = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (my_sign == -1)
		result = -output;
	else
		result = output;

	return (result);
}
