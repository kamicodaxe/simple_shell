#include "shell.h"

/**
 * _strlen - Returns the length of string
 * @str: string input pointer
 * Return: Length of string
 */
int _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * _strchr - Locates the first occurrence of a character in a string
 * @str: The string to search
 * @character: The character to locate
 *
 * Return: If the character is found, a pointer to the first occurrence
 * in the string; otherwise, NULL.
 */
char *_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
		{
			return ((char *)str);
		}
		str++;
	}

	return (NULL);
}
