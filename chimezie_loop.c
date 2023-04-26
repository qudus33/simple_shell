#include "chimezie_shell.h"

/**
 * hsh - The main shell loop
 * @infomat: The parameter & return info structure
 * @arv: The argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *infomat, char **arv)
{
	ssize_t g = 0;
	int built_in_res = 0;

	while (g != -1 && built_in_res != -2)
	{
		clear_infor(infomat);
		if (inter_active(infomat))
			_puts("$ ");
		_dputchar(BUF_FLUSH);
		g = get_input(infomat);
		if (g != -1)
		{
			set_infor(infomat, arv);
			built_in_res = find_built_in(infomat);
			if (built_in_res == -1)
				find_cmd(infomat);
		}
		else if (inter_active(infomat))
			_putchar('\n');
		free_infor(infomat, 0);
	}
	write_history(infomat);
	free_infor(infomat, 1);
	if (!inter_active(infomat) && infomat->status)
		exit(infomat->status);
	if (built_in_res == -2)
	{
		if (infomat->err_numba == -1)
			exit(infomat->status);
		exit(infomat->err_numba);
	}
	return (built_in_res);
}

/**
 * find_built_in - A function that finds a builtin command
 * @infomat: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_built_in(info_t *infomat)
{
	int n, built_in_res = -1;
	built_in_table built_intbl[] = {
		{"exit", _my_xit},
		{"env", _my_env},
		{"help", _my_help},
		{"history", _my_history},
		{"setenv", _my_set_env},
		{"unsetenv", _my_unset_nv},
		{"cd", _my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (n = 0; built_intbl[n].type_b; n++)
		if (_strcmp(infomat->argv[0], built_intbl[n].type_b) == 0)
		{
			infomat->line_count++;
			built_in_res = built_intbl[n].func(infomat);
			break;
		}
	return (built_in_res);
}

/**
 * find_cmd - A function that finds a command in PATH
 * @infomat: The parameter and return information structure
 *
 * Return: void
 */
void find_cmd(info_t *infomat)
{
	char *way = NULL;
	int n, k;

	infomat->path = infomat->argv[0];
	if (info_t->line_count_flag == 1)
	{
		infomat->line_count++;
		infomat->linecount_flag = 0;
	}
	for (n = 0, k = 0; infomat->arg[n]; n++)
		if (!is_delim(infomat->arg[n], " \t\n"))
			k++;
	if (!k)
		return;

	way = find_path(infomat, _get_env(infomat, "PATH="), infomat->argv[0]);
	if (way)
	{
		infomat->path = path;
		fork_cmd(infomat);
	}
	else
	{
		if ((inter_active(infomat) || _get_env(infomat, "PATH=")
			|| infomat->argv[0][0] == '/') && a_cmd(infomat, infomat->argv[0]))
			fork_cmd(infomat);
		else if (*(infomat->arg) != '\n')
		{
			infomat->status = 127;
			print_error(infomat, "Not found\n");
		}
	}
}

/**
 * fork_cmd - A function forks and executes thread to run command
 * @infomat: The parameter & return infomation structure
 *
 * Return: void
 */
void fork_cmd(info_t *infomat)
{
	pid_t childs_pid;

	childs_pid = fork();
	if (childs_pid == -1)
	{
		/* A FUNCTION THAT PUTS ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childs_pid == 0)
	{
		if (execve(infomat->path, infomat->argv, get_environs(infomat)) == -1)
		{
			free_info(infomat, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* A FUNCTION THAT PUTS ERROR FUNCTION */
	}
	else
	{
		wait(&(infomat->status));
		if (WIFEXITED(infomat->status))
		{
			infomat->status = WEXITSTATUS(infomat->status);
			if (infomat->status == 126)
				print_error(infomat, "The Permission has been denied\n");
		}
	}
}
