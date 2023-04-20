#include "shell.h"

/**
 * add_nodes - A function that adds a node to the start of the list
 * @head: The address of pointer to head node
 * @string: The string field of node
 * @numba: The node index used by history
 *
 * Return: size of list
 */
list_t *add_nodes(list_t **head, const char *string, int numba)
{
	list_t *first_head;

	if (!head)
		return (NULL);
	first_head = malloc(sizeof(list_t));
	if (!first_head)
		return (NULL);
	_memset((void *)first_head, 0, sizeof(list_t));
	first_head->numba = numba;
	if (string)
	{
		first_head->string = _strdup(string);
		if (!first_head->string)
		{
			free(first_head);
			return (NULL);
		}
	}
	first_head->next = *head;
	*head = first_head;
	return (first_head);
}

/**
 * add_nodes_end - A function that adds a node to the end of the list
 * @head: Address of pointer to head node
 * @string: string field of node
 * @numba: node index used by history
 *
 * Return: size of list
 */
list_t *add_nodes_end(list_t **head, const char *string, int numba)
{
	list_t *first_node, *nodes;

	if (!head)
		return (NULL);

	nodes = *head;
	first_node = malloc(sizeof(list_t));
	if (!first_node)
		return (NULL);
	_memset((void *)first_node, 0, sizeof(list_t));
	first_node->numba = numba;
	if (string)
	{
		first_node->string = _strdup(string);
		if (!first_node->string)
		{
			free(first_node);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = first_node;
	}
	else
		*head = first_node;
	return (first_node);
}

/**
 * print_list_string - Function that prints only
 * the string element of a list_t linked list
 * @m: A pointer to first node
 *
 * Return: size of list
 */
size_t print_list_string(const list_t *m)
{
	size_t n = 0;

	while (m)
	{
		_puts(m->string ? m->string : "(NIL)");
		_puts("\n");
		m = m->next;
		n++;
	}
	return (n);
}

/**
 * delete_nodes_at_index - A function that deletes node at given index
 * @head: Address of pointer to first node
 * @indess: The index of nodes to be deleted
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nodes_at_index(list_t **head, unsigned int indess)
{
	list_t *nodes, *last_node;
	unsigned int n = 0;

	if (!head || !*head)
		return (0);

	if (!indess)
	{
		nodes = *head;
		*head = (*head)->next;
		free(nodes->string);
		free(nodes);
		return (1);
	}
	nodes = *head;
	while (nodes)
	{
		if (n == indess)
		{
			last_node->next = nodes->next;
			free(nodes->string);
			free(nodes);
			return (1);
		}
		n++;
		last_node = nodes;
		nodes = nodes->next;
	}
	return (0);
}

/**
 * free_lists - A function that frees all nodes of a list
 * @head_ptar: address of pointer to head node
 *
 * Return: void
 */
void free_lists(list_t **head_ptar)
{
	list_t *nodes, *next_node, *head;

	if (!head_ptar || !*head_ptar)
		return;
	head = *head_ptar;
	nodes = head;
	while (nodes)
	{
		next_node = nodes->next;
		free(nodes->string);
		free(nodes);
		nodes = next_node;
	}
	*head_ptar = NULL;
}
