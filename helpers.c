#include "shell.h"

/**
 * _memset - fill memory with a constant byte
 * @p: buffer
 * @b: byte
 * @n: number of bytes to write
 *
 * Return: Pointer to memory after filling
 */
char *_memset(void *p, char b, unsigned int n)
{
	unsigned int i = 0;
	char *s = (char *)p;

	for (i = 0; i < n; i++)
		*(s + i) = b;
	return (s);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = (char *)(flags & CONVERT_LOWERCASE ? "0123456789abcdef"
											   : "0123456789ABCDEF");
	ptr = &buffer[49];
	*ptr = '\0';

	/* clang-format off */
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	/* clang-format on */

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _realloc - allocate memory and set all values to 0
 * @ptr: pointer to the memory previously allocated (malloc(old_size))
 * @old_size: size previously allocated
 * @new_size: new size to reallocate
 *
 * Return: pointer to reallocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int i;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (p == NULL)
		return (NULL);

	if (ptr == NULL)
		return (p);

	for (i = 0; i < old_size && i < new_size; i++)
		*((char *)p + i) = *((char *)ptr + i);
	free(ptr);

	return (p);
}
