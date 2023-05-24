#include "shell.h"

/**
 * _strcmp - compare strings
 * @s1: string
 * @s2: string
 *
 * Return: Difference between the first unmatched character
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenate strings
 * @dest: destination, string
 * @src: source, string
 *
 * Return: Pointer to destination after concatenation
 */
char *_strcat(char *dest, char *src)
{
	char *dest_copy = dest;

	while (*(dest_copy++ + 1) != '\0')
		;
	while ((*dest_copy++ = *src++) != '\0')
		;
	return (dest);
}

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = (char **)malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		int k = 0;

		while (is_delim(str[i], d))
			i++;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = (char *)malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * _strchr - find character in string
 * @s: String to search from
 * @c: Character to search for
 *
 * Return: Pointer to first occurence of character
 */
char *_strchr(char *s, char c)
{
	/* clang-format off */
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	/* clang-format on */

	return (NULL);
}
