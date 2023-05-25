#include "shell.h"

/**
 * build_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int build_env_list(Shell_info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * getenv_with_key - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @key: env var key
 *
 * Return: the value
 */
char *getenv_with_key(Shell_info_t *info, const char *key)
{
	list_t *node = info->env;

	while (node)
	{
		char *p = starts_with(node->str, key);

		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(Shell_info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;

	if (!var || !value)
		return (0);
	buf = (char *)malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		char *p = starts_with(node->str, var);

		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * get_environ - returns the string array copy of our environ
 * @info: Shell_info_t
 *
 * Return: Pointer to environ stored in Shell_info
 */
char **get_environ(Shell_info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
