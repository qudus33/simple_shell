#include "chimezie_shell.h"

/**
 * main - The entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t infomat[] = { INFO_INIT };
	int file_des = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_des)
		: "r" (file_des));

	if (ac == 2)
	{
		file_des = open(av[1], O_RDONLY);
		if (file_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infomat->readfd = file_des;
	}
	populate_env_list(infomat);
	read_history(infomat);
	hsh(infomat, av);
	return (EXIT_SUCCESS);
}
