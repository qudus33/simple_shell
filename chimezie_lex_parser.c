#include "shell.h"

/**
 * a_cmd - A fuction that determines if a file is an executable command
 * @infomat: The information structure
 * @way: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int a_cmd(info_t *infomat, char *way)
{
	struct status sp;

	(void)infomat;
	if (!way || status(way, &sp))
		return (0);

	if (sp.sp_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupe_chars - A function that duplicates characters
 * @waystring: the PATH string
 * @first: starting index
 * @end: stopping index
 *
 * Return: A pointer to new buffer
 */
char *dupe_chars(char *waystring, int first, int end)
{
	static char buffa[1024];
	int n = 0, t = 0;

	for (t = 0, n = first; n < end; n++)
		if (waystring[n] != ':')
			buffa[t++] = waystring[n];
	buffa[t] = 0;
	return (buffa);
}

/**
 * find_path - A function that finds this cmd in the PATH string
 * @infomat: The information structure
 * @waystring: the PATH string
 * @comand: The command to find
 *
 * Return: The full path of the command if found or NULL
 */
char *find_path(info_t *infomat, char *waystring, char *comand)
{
	int n = 0, current_position = 0;
	char *way;

	if (!waystring)
		return (NULL);
	if ((_strlen(comand) > 2) && starts_with(comand, "./"))
	{
		if (a_cmd(infomat, comand))
			return (cmd);
	}
	while (1)
	{
		if (!waystring[n] || waystring[n] == ':')
		{
			way = dupe_chars(waystring, current_position, n);
			if (!*way)
				_strcat(way, comand);
			else
			{
				_strcat(way, "/");
				_strcat(way, comand);
			}
			if (a_cmd(infomat, way))
				return (way);
			if (!waystring[n])
				break;
			current_position = n;
		}
		n++;
	}
	return (NULL);
}
