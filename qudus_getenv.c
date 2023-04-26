#include "shell.h"

/**
 * get_environ - gets the string array copy of our environ
 * @info: Structure containing potential args. Used to maintain
 *          constant function prototype.
 * Return: returns 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an env var.
 * @info: Structure contains potential args. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 *  Return: returns 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *my_node = info->env;
	size_t t = 0;
	char *r;

	if (!my_node || !var)
		return (0);

	while (my_node)
	{
		r = starts_with(my_node->str, var);
		if (r && *r == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), t);
			t = 0;
			my_node = info->env;
			continue;
		}
		my_node = my_node->next;
		t++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environ var,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: string environ var properties
 * @value: string environ var value
 *  Return: returns 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *my_node;
	char *t;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	my_node = info->env;
	while (my_node)
	{
		t = starts_with(my_node->str, var);
		if (t && *t == '=')
		{
			free(my_node->str);
			my_node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		my_node = my_node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
