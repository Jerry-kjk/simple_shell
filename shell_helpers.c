#include "shell.h"

/**
 * clear_info - initializes Shell_info_t struct
 * @shell_info: struct address
 */
void clear_info(Shell_info_t *shell_info)
{
	shell_info->arg = NULL;
	shell_info->argv = NULL;
	shell_info->path = NULL;
	shell_info->argc = 0;
}

/**
 * set_info - initializes Shell_info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(Shell_info_t *info, char **av)
{

	info->fname = av[0];
	if (info->arg)
	{
		int i = 0;

		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = (char **)malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
static void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
static int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_info - frees Shell_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(Shell_info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));

		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
