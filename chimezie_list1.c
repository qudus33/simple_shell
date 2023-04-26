#include "chimezie_shell.h"

/**
 * list_lens - A function that determines length of linked list
 * @m: pointer to first node
 *
 * Return: size of list
 */
size_t list_lens(const list_t *m)
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
 * list_to_string - A function that returns an
 * array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_string(list_t *head)
{
	list_t *nodes = head;
	size_t n = list_lens(head), l;
	char **strings;
	char *string;

	if (!head || !n)
		return (NULL);
	strings = malloc(sizeof(char *) * (n + 1));
	if (!strings)
		return (NULL);
	for (n = 0; nodes; nodes = nodes->next, n++)
	{
		string = malloc(_strlen(nodes->string) + 1);
		if (!string)
		{
			for (l = 0; l < n; l++)
				free(strings[l]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, nodes->string);
		strings[n] = string;
	}
	strings[n] = NULL;
	return (strings);
}


/**
 * print_lists - A function that prints
 * all elements of a list_t linked list
 * @m: A pointer to first node
 *
 * Return: size of list
 */
size_t print_lists(const list_t *m)
{
	size_t n = 0;

	while (m)
	{
		_puts(convert_number(m->numba, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(m->string ? m->string : "(NIL)");
		_puts("\n");
		m = m->next;
		n++;
	}
	return (n);
}

/**
 * nodes_starts_with - A function that returns node
 * whose string starts with prefix
 * @nodes: A pointer to list head
 * @prefiss: string to match
 * @b: The next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodes_starts_with(list_t *nodes, char *prefiss, char b)
{
	char *q = NULL;

	while (nodes)
	{
		q = starts_with(nodes->string, prefiss);
		if (q && ((b == -1) || (*q == b)))
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * get_nodes_index - A function that gets the index of a node
 * @head: A pointer to list head
 * @nodes: A pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_nodes_index(list_t *head, list_t *nodes)
{
	size_t n = 0;

	while (head)
	{
		if (head == nodes)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
