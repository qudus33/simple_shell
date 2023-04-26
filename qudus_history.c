#include "shell.h"

/**
 * get_history_file - function to get history file.
 * @info: struct param
 *
 * Return: returns allocated string contained in history file
 */

char *get_history_file(info_t *info)
{
	char *buff, *my_dir;

	my_dir = _getenv(info, "HOME=");
	if (!my_dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(my_dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, my_dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates file or appends to existing file.
 * @info: param struct
 *
 * Return: returns 1 on success or -1 or error
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *fileName = get_history_file(info);
	list_t *my_node = NULL;

	if (!fileName)
		return (-1);

	fd = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileName);
	if (fd == -1)
		return (-1);
	for (my_node = info->history; my_node; my_node = my_node->next)
	{
		_putsfd(my_node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - from file
 * @info: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_history(info_t *info)
{
	int t, last = 0, line_Count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *fileName = get_history_file(info);

	if (!fileName)
		return (0);

	fd = open(fileName, O_RDONLY);
	free(fileName);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (t = 0; t < fsize; t++)
		if (buf[t] == '\n')
		{
			buf[t] = 0;
			build_history_list(info, buf + last, line_Count++);
			last = t + 1;
		}
	if (last != t)
		build_history_list(info, buf + last, line_Count++);
	free(buf);
	info->histcount = line_Count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Struct contains potential args. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *my_node = NULL;

	if (info->history)
		my_node = info->history;
	add_node_end(&my_node, buf, linecount);

	if (!info->history)
		info->history = my_node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int renumber_history(info_t *info)
{
	list_t *my_node = info->history;
	int j = 0;

	while (my_node)
	{
		my_node->num = j++;
		my_node = my_node->next;
	}
	return (info->histcount = j);
}
