#include "chimezie_shell.h"

/**
 * y_cmd - Determines whether a file is an executable command
 * @info: information structure for the program
 * @path: direction to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int y_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: A pointer to a new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char _buffer[1024];
	int n = 0, t = 0;

	for (t = 0, n = start; n < stop; n++)
		if (pathstr[n] != ':')
			_buffer[t++] = pathstr[n];
	_buffer[t] = 0;
	return (_buffer);
}

/**
 * find_path - A function that finds this cmd in the PATH string
 * @info: The information structure
 * @pathstr: the PATH string
 * @cmd: The command to find
 *
 * Return: The full path of the command if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int n = 0, current_position = 0;
	char *way;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (y_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			way = dup_chars(pathstr, current_position, n);
			if (!*way)
				_strcat(way, cmd);
			else
			{
				_strcat(way, "/");
				_strcat(way, cmd);
			}
			if (y_cmd(info, way))
				return (way);
			if (!pathstr[n])
				break;
			current_position = n;
		}
		n++;
	}
	return (NULL);
}
