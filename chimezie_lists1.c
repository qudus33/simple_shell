#include "chimezie_shell.h"

/**
 * lists_lents - A function that determines length of linked list
 * @m: pointer to first node
 *
 * Return: size of list
 */

size_t lists_lents(const list_t *m)
{
	size_t n = 0;

	while (m)
	{
		m = m->next;
		n++;
	}
	return (n);
}

/**
 * lists_to_strings - A function that returns an
 * array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **lists_to_strings(list_t *head)
{
	list_t *nodes = head;
	size_t i = lists_lents(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nodes; nodes = nodes->next, i++)
	{
		str = malloc(_strlen(nodes->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nodes->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * prints_lists - A function that prints
 * all elements of a list_t linked list
 * @m: A pointer to first node
 *
 * Return: size of list
 */

size_t prints_lists(const list_t *m)
{
	size_t n = 0;

	while (m)
	{
		_puts(convert_number(m->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(m->str ? m->str : "(nil)");
		_puts("\n");
		m = m->next;
		n++;
	}
	return (n);
}

/**
 * node_starts_with - A function that returns node
 * whose string starts with prefix
 * @node: A pointer to list head
 * @prefix: string to match
 * @c: The next character after prefix to match
 *
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *q = NULL;

	while (node)
	{
		q = starts_with(node->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - A function that gets the index of a node
 * @head: A pointer to list head
 * @node: A pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
