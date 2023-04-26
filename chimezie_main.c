#include "chimezie_shell.h"

/**
 * main - The entry point
 * @ab: Argument count
 * @arv: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ab, char **arv)
{
	info_t infomat[] = { INFO_INIT };
	int file_dir = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_dir)
		: "r" (file_dir));

	if (ab == 2)
	{
		file_dir = open(arv[1], O_RDONLY);
		if (file_dir == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_dputs(arv[0]);
				_dputs(": 0: Can't open ");
				_dputs(arv[1]);
				_dputchar('\n');
				_dputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infomat->readfile_dir = file_dir;
	}
	populates_env_list(infomat);
	read_history(infomat);
	hsh(infomat, arv);
	return (EXIT_SUCCESS);
}
