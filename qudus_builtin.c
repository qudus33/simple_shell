#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure has potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: return the exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int checkExit;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		checkExit = _erratoi(info->argv[1]);
		if (checkExit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change current directory on process
 * @info: Structure contains potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: reurns 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int _chdir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			_chdir = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			_chdir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		_chdir = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		_chdir = chdir(info->argv[1]);
	if (_chdir == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes current directory of the process
 * @info: Structure contains potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: returns 0
 */

int _myhelp(info_t *info)
{
	char **array_args;

	array_args = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*array_args); /* temp att_unused workaround */
	return (0);
}
