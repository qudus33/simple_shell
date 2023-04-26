#include "chimezie_shell.h"

/**
 * **strtow - A function that splits a string into words.
 * Repeat delimiters are ignored
 * @string: The input string
 * @del: The delimeter string
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */

char **strtow(char *string, char *del)
{
	int i, t, k, n, numba_words = 0;
	char **str;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(string[i], del) && (is_delim(string[i + 1], del)
		|| !string[i + 1]))
			numba_words++;

	if (numba_words == 0)
		return (NULL);
	str = malloc((1 + numba_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, t = 0; t < numba_words; t++)
	{
		while (is_delim(string[i], del))
			i++;
		k = 0;
		while (!is_delim(string[i + k], del) && string[i + k])
			k++;
		str[t] = malloc((k + 1) * sizeof(char));
		if (!str[t])
		{
			for (k = 0; k < t; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			str[t][n] = string[i++];
		str[t][n] = 0;
	}
	str[t] = NULL;
	return (str);
}

/**
 * **strtow2 - A function that splits a string into words
 * @string: The input string
 * @del: The delimeter
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char del)
{
	int i, t, k, n, numba_words = 0;
	char **str;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != del && string[i + 1] == del) ||
		    (string[i] != del && !string[i + 1]) || string[i + 1] == del)
			numba_words++;
	if (numba_words == 0)
		return (NULL);
	str = malloc((1 + numba_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, t = 0; t < numba_words; t++)
	{
		while (string[i] == del && string[i] != del)
			i++;
		k = 0;
		while (string[i + k] != del && string[i + k] && string[i + k] != del)
			k++;
		str[t] = malloc((k + 1) * sizeof(char));
		if (!str[t])
		{
			for (k = 0; k < t; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			str[t][n] = string[i++];
		str[t][n] = 0;
	}
	str[t] = NULL;
	return (str);
}
