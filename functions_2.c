#include "shell.h"

/**
 * handle_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int handle_setenv(Shell_info_t *info)
{
	if (info->argc != 3)
	{
		puts_error("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
static int _unsetenv(Shell_info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;

	if (!node || !var)
		return (0);
	while (node)
	{
		char *p = starts_with(node->str, var);

		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * handle_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int handle_unsetenv(Shell_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		puts_error("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}
