#include "shell.h"

/**
 * shell_run - main shell loop
 * @shell_info: the parameter & return shell_info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_run(Shell_info_t *shell_info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(shell_info);
		if (interactive(shell_info))
			_puts((char *)"$ ");
		putchar_error(BUFFER_FLUSH);
		r = get_input(shell_info);
		if (r != -1)
		{
			set_info(shell_info, av);
			builtin_ret = find_builtin(shell_info);
			if (builtin_ret == -1)
				find_cmd(shell_info);
		}
		else if (interactive(shell_info))
			_putchar('\n');
		free_info(shell_info, 0);
	}
	write_history(shell_info);
	free_info(shell_info, 1);
	if (!interactive(shell_info) && shell_info->status)
		exit(shell_info->status);
	if (builtin_ret == -2)
	{
		if (shell_info->err_num == -1)
			exit(shell_info->status);
		exit(shell_info->err_num);
	}
	return (builtin_ret);
}
