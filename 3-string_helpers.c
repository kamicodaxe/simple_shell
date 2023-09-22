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
 * _strdup - A function that duplicates
 * a string
 * @s: original string to duplicate
 * Return: pointer to the value of the duplicate string
 */
char *_strdup(char *s)
{
	size_t len;
	char *d;

	if (s == NULL)
		return (NULL);
	len = _strlen(s);
	d = (char *)malloc(len + 1);
	if (d == NULL)
		return (NULL);
	return (_strcpy(d, s));
}
