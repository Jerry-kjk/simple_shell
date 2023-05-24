#include "shell.h"

/**
 * putchar_error - writes character to stderr
 * @c: character to print
 *
 * Return: 1 on success, -1 otherwise. `errno` is set
 */
int putchar_error(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUFFER_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * puts_error - prints an input string to standard error
 * @str: string to print
 *
 */
void puts_error(char *str)
{
	int c;

	if (!str)
		return;

	while ((c = *(str++)) != '\0')
		putchar_error(c);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
static int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = putchar_error;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_error(Shell_info_t *info, char *estr)
{
	puts_error(info->fname);
	puts_error(": ");
	print_d(info->line_count, STDERR_FILENO);
	puts_error(": ");
	puts_error(info->argv[0]);
	puts_error(": ");
	puts_error(estr);
}
