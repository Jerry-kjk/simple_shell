#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: 1 on success, -1 otherwise. `errno` is set
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _puts - Print string
 * @str: pointer to char type (string)
 *
 */
void _puts(char *str)
{
	char c;

	while ((c = *(str++)) != '\0')
		_putchar(c);
}

/**
 * _strcpy - Copy string from source to destination
 * @dest: pointer to destination
 * @src: pointer to source
 *
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, char *src)
{
	char c;
	char *dest_copy = dest;

	while ((c = *src++) != '\0')
		*dest_copy++ = c;
	*dest_copy = '\0';

	return (dest);
}

/**
 * _strdup - allocate space in memory, copy string given as a parameter
 * @str: given string
 *
 * Return: pointer to duplicated string
 */
char *_strdup(const char *str)
{
	unsigned int len = 0, i = 0;
	char *dup = NULL;

	if (str == NULL)
		return (dup);

	while (str[len++])
		;

	dup = (char *)malloc(len);
	if (dup == NULL)
		return (dup);

	for (i = 0; i < len; i++)
		dup[i] = str[i];

	return (dup);
}

/**
 * _strlen - Compute length of string
 * @s: pointer to char type (string)
 *
 * Return: Length of string `int`
 */
int _strlen(char *s)
{
	int len = 0;

	while (*(s++) != '\0')
		len++;

	return (len);
}
