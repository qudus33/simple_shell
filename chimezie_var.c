#include "chimezie_shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t w = *p;

	if (buf[w] == '|' && buf[w + 1] == '|')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[w] == '&' && buf[w + 1] == '&')
	{
		buf[w] = 0;
		w++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[w] == ';') /* found end of this command */
	{
		buf[w] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = w;
	return (1);
}

/**
 * check_chain - A function that checks if we should
 * continue chaining based on last status
 * @info: The parameter structure
 * @buf: The character buffer
 * @p: address of current position in buf
 * @i: The starting position in a buf
 * @len: The length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t g = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}

	*p = g;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int t;
	list_t *nodes;
	char *g;

	for (t = 0; t < 10; t++)
	{
		nodes = node_starts_with(info->alias, info->argv[0], '=');
		if (!nodes)
			return (0);
		free(info->argv[0]);
		g = _strchr(nodes->str, '=');
		if (!g)
			return (0);
		g = _strdup(g + 1);
		if (!g)
			return (0);
		info->argv[0] = g;
	}
	return (1);
}

/**
 * replace_vars - A function that replaces vars in the
 *                tokenized string
 * @info: The parameter structure
 *
 * Return: returns 1 if replaced or 0 otherwise
 */
int replace_vars(info_t *info)
{
	int t = 0;
	list_t *nodes;

	for (t = 0; info->argv[t]; t++)
	{
		if (info->argv[t][0] != '$' || !info->argv[t][1])
			continue;

		if (!_strcmp(info->argv[t], "$?"))
		{
			replace_string(&(info->argv[t]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[t], "$$"))
		{
			replace_string(&(info->argv[t]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nodes = node_starts_with(info->env, &info->argv[t][1], '=');
		if (nodes)
		{
			replace_string(&(info->argv[t]),
				_strdup(_strchr(nodes->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[t], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @pre: address of old string
 * @lat: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **pre, char *lat)
{
	free(*pre);
	*pre = lat;
	return (1);
}
