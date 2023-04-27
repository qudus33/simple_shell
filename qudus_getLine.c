#include "chimezie_shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_s = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_s, stdin);
#else
		s = _getline(info, buf, &len_s);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - prints a line minus the newline
 * @info: parameter struct
 *
 * Return: returns bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_s = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buff, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buff position */
		p = buff + i; /* get pointer for return */

		check_chain(info, buff, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_s = p;
		return (_strlen(p));
	}

	*buf_s = buff;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @info: specify parameter struct
 * @buf: specify buffer
 * @i: is size
 *
 * Return: returns b
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t b = 0;

	if (*i)
		return (0);
	b = read(info->readfd, buf, READ_BUF_SIZE);
	if (b >= 0)
		*i = b;
	return (b);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: the parameter struct
 * @ptr: the address of pointer to buffer, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 *
 * Return: return s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t q, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (q == len)
		q = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + q, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + q, k - q);
	else
		_strncpy(new_p, buf + q, k - q + 1);

	s += k - q;
	q = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - ctrl-C is blocked
 * @sig_num: the signal number
 *
 * Return: returns void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
