#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

int _erratoi(char *s)
{
	int t = 0;
	unsigned long int my_value = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (t = 0;  s[t] != '\0'; t++)
	{
		if (s[t] >= '0' && s[t] <= '9')
		{
			my_value *= 10;
			my_value += (s[t] - '0');
			if (my_value > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (my_value);
}

/**
 * print_error - print error messages
 * @info: parameter & return info struct
 * @estr: the string containing specified error type
 * Return: returns 0 if no numbers in string
 * converted number, return -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal (integer) number (base 10)
 * @input: input value
 * @fd: file descriptor written to
 *
 * Return: returns num of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int p, num = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		num++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (p = 1000000000; p > 1; p /= 10)
	{
		if (_abs_ / p)
		{
			__putchar('0' + current / p);
			num++;
		}
		current %= p;
	}
	__putchar('0' + current);
	num++;

	return (num);
}

/**
 * convert_number - convert a number to base
 * @num: number value
 * @base: base
 * @flags: argument flags
 *
 * Return: returns the string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char my_sign = 0;
	char *pntr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		my_sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pntr = &buffer[49];
	*pntr = '\0';

	do	{
		*--pntr = array[n % base];
		n /= base;
	} while (n != 0);

	if (my_sign)
		*--pntr = my_sign;
	return (pntr);
}

/**
 * remove_comments - replaces 1st instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int r;

	for (r = 0; buf[r] != '\0'; r++)
		if (buf[r] == '#' && (!r || buf[r - 1] == ' '))
		{
			buf[r] = '\0';
			break;
		}
}
