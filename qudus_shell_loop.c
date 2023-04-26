#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t s = 0;
	int bltin_ret = 0;

	while (s != -1 && bltin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, av);
			bltin_ret = find_builtin(info);
			if (bltin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (bltin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bltin_ret);
}

/**
 * find_builtin - builtin command locator
 * @info: parameter & return info struct
 *
 * Return: -1 if the builtin not found,
 *			0 if the builtin executed successfully,
 *			1 if the builtin found but not successful,
 *			-2 if the builtin signals exit
 */
int find_builtin(info_t *info)
{
	int p, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (p = 0; builtintbl[p].type; p++)
		if (_strcmp(info->argv[0], builtintbl[p].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[p].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - find command in PATH dir
 * @info: parameter & return info struct
 *
 * Return: returns void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int p, q;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (p = 0, q = 0; info->arg[p]; p++)
		if (!is_delim(info->arg[p], " \t\n"))
			q++;
	if (!q)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks and exec thread to run cmd
 * @info: parameter & return info struct
 *
 * Return: returns void
 */
void fork_cmd(info_t *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
