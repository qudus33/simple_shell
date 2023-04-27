#include "chimezie_shell.h"

/**
 * _myenv - print current environment
 * @info: Structure contains possible arguments.To maintain
 *          constant function prototype.
 * Return: returns 0
 */
int _myenv(info_t *info)
{
	prints_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *i;

	while (node)
	{
		i = starts_with(node->str, name);
		if (i && *i)
			return (i);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove environment variable
 * @info: Structure contains potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: returns 0
 */

int _myunsetenv(info_t *info)
{
	int p;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (p = 1; p <= info->argc; p++)
		_unsetenv(info, info->argv[p]);

	return (0);
}

/**
 * populate_env_list - populate environ linked list
 * @info: Structure contains potential arguments. To maintain
 *          constant function prototype.
 * Return: returns 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_nodes_end(&node, environ[k], 0);
	info->env = node;
	return (0);
}
