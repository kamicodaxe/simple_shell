#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: char
 * @s2: char
 * Return: int
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}

/**
 * _strncmp - A function that compares two strings
 * @s1: first pointer parameter of type char
 * @s2: second pointer parameter of type char
 * @n: number of characters to compare
 *
 * Return: Always 0 (Success)
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 && n > 0)
	{
		if (*s1 != *s2)
		{
			break;
		}
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);

	/* return ascii difference after converting *char to unsigned *char */
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strdup - A function that duplicates
 * a string
 * @s: original string to duplicate
 * Return: pointer to the value of the duplicate string
 */
char *_strdup(char *s)
{
	char *d;
	int len;

	if (s == NULL)
		return (NULL);
	len = _strlen(s);
	d = (char *)malloc(len + 1); /* allocate memory */

	if (d == NULL)
	{
		perror("_strdup malloc:");
		exit(EXIT_FAILURE);
	}
	_strcpy(d, s);
	return (d);
}
