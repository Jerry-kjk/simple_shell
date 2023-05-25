#include "shell.h"

/**
 * print_enoent - print ENOENT error
 * @command: command
 * @filename: filename
 *
 */
static void print_enoent(char *command, char *filename)
{
	puts_error(command);
	puts_error(": 0: Can't open ");
	puts_error(filename);
	putchar_error('\n');
	putchar_error(BUFFER_FLUSH);
}

/**
 * main - Entry point
 * @argc: number of command line arguments
 * @argv: array of strings containing command line arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	Shell_info_t shell_info = SHELL_INFO_INIT;

	if (argc == 2)
	{
		int fd = open(argv[1], O_RDONLY);

		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_enoent(argv[0], argv[1]);
				exit(127);
			}

			return (EXIT_FAILURE);
		}
		shell_info.fd = fd;
	}

	shell_run(&shell_info, argv);

	return (EXIT_SUCCESS);
}
