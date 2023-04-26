#include "shell.h"

/**
 *_eputs - print an input string
 * @str: specifies the string to be printed
 *
 * Return: Null
 */

void _eputs(char *str)
{
	int r = 0;

	if (!str)
		return;
	while (str[r] != '\0')
	{
		_eputchar(str[r]);
		r++;
	}
}

/**
 * _eputchar - write a char to stderr
 * @c: specifies the char to print
 *
 * Return: 1 on success.
 * -1 on error.
 */

int _eputchar(char c)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(2, buf, r);
		r = 0;
	}
	if (c != BUF_FLUSH)
		buf[r++] = c;
	return (1);
}

/**
 * _putfd - write a char to a specified file descriptor
 * @c: char to print.
 * @fd: file descriptor.
 *
 * Return: return 1 on success.
 * return -1 on error.
 */

int _putfd(char c, int fd)
{
	static int s;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(fd, buf, s);
		s = 0;
	}
	if (c != BUF_FLUSH)
		buf[s++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: strings to be printed
 * @fd: file descriptor to write
 *
 * Return: returns number of char entered
 */

int _putsfd(char *str, int fd)
{
	int t = 0;

	if (!str)
		return (0);
	while (*str)
	{
		t += _putfd(*str++, fd);
	}
	return (t);
}
