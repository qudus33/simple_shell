#include "chimezie_shell.h"

/**
 * d_chain - A function that tests if current
 * character in buffer is a chain delimeter
 * @infomat: The parameter structure
 * @buffa: The character buffer
 * @pos: The address of current position in buffa
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int d_chain(info_t *infomat, char *buffa, size_t *pos)
{
	size_t t = *pos;

	if (buffa[t] == '|' && buffa[t + 1] == '|')
	{
		buffa[t] = 0;
		t++;
		infomat->cmd_buffa_type = CMD_OR;
	}
	else if (buffa[t] == '&' && buffa[t + 1] == '&')
	{
		buffa[t] = 0;
		t++;
		infomat->cmd_buffa_type = CMD_AND;
	}
	else if (buffa[t] == ';')
	{
		buffa[t] = 0;
		infomat->cmd_buffa_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = t;
	return (1);
}

/**
 * checks_chain - A function that checks if we should
 * continue chaining based on last status
 * @infomat: The parameter structure
 * @buffa: The character buffer
 * @pos: address of current position in buf
 * @init: The starting position in a buffa
 * @lent: The length of buffa
 *
 * Return: Void
 */
void checks_chain(info_t *infomat, char *buffa, size_t *pos, size_t init, size_t lent)
{
	size_t t = *pos;

	if (infomat->cmd_buffa_type == CMD_AND)
	{
		if (infomat->status)
		{
			buffa[init] = 0;
			t = lent;
		}
	}
	if (infomat->cmd_buffa_type == CMD_OR)
	{
		if (!infomat->status)
		{
			buffa[init] = 0;
			t = lent;
		}
	}

	*pos = t;
}

/**
 * replaces_alias - A function that replaces an aliases in the tokenized string
 * @infomat: The parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_alias(info_t *infomat)
{
	int n;
	list_t *nodes;
	char *pos;

	for (n = 0; n < 10; n++)
	{
		nodes = nodes_starts_with(infomat->alias, infomat->argv[0], '=');
		if (!nodes)
			return (0);
		free(infomat->argv[0]);
		p = _strchr(nodes->string, '=');
		if (!pos)
			return (0);
		pos = _strdup(pos + 1);
		if (!pos)
			return (0);
		infomat->argv[0] = pos;
	}
	return (1);
}

/**
 * replaces_var - A function that replaces vars in the tokenized string
 * @infomat: The parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_var(info_t *infomat)
{
	int n = 0;
	list_t *nodes;

	for (n = 0; infomat->argv[n]; n++)
	{
		if (infomat->argv[n][0] != '$' || !infomat->argv[n][1])
			continue;

		if (!_strcmp(infomat->argv[n], "$?"))
		{
			replaces_string(&(infomat->argv[i]),
				_strdup(convert_numbers(infomat->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infomat->argv[i], "$$"))
		{
			replaces_string(&(infomat->argv[n]),
				_strdup(convert_numbers(getpid(), 10, 0)));
			continue;
		}
		nodes = nodes_starts_with(infomat->env, &infomat->argv[n][1], '=');
		if (nodes)
		{
			replaces_string(&(infomat->argv[n]),
				_strdup(_strchr(nodes->string, '=') + 1));
			continue;
		}
		replaces_string(&infomat->argv[n], _strdup(""));

	}
	return (0);
}

/**
 * replaces_str - A function that replaces string
 * @pre: The address of old string
 * @lat: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_str(char **pre, char *lat)
{
	free(*pre);
	*pre = lat;
	return (1);
}
