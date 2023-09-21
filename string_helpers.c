#include "shell.h"
#include <stdio.h>

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
 * _strcpy - A function that copies the string pointed
 * to by src,including the terminating null byte \0
 * to the buffer pointed to by dest.
 * @dest: Pointer char, destination of copy
 * @src: Pointer char, source of copy
 *
 * Return: The pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (; src[i]; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * trimLeft - Removes leading white spaces
 * @str: A pointer to the input string
 */
void trimLeft(char *str)
{
	int i, spaceFlag, length = 0, start = 0;

	if (str == NULL)
		return;

	while (str[length] != '\0')
		length++;

	/* Find index of the first non-whitespace character */
	while (start < length &&
		   (str[start] == ' ' || str[start] == '\t' || str[start] == '\n'))
		start++;

	/* If all leading characters are whitespace, str[start] will be '\0' */
	if (start > 0)
	{
		i = 0;
		spaceFlag = 0; /* Flag to keep track of single space */
		/* Shift the string left to remove leading whitespace */
		while (str[start] != '\0')
		{
			if (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
			{
				if (!spaceFlag)
				{
					str[i] = ' ';
					i++;
					spaceFlag = 1; /* Set flag to avoid multiple spaces */
				}
			}
			else
			{
				str[i] = str[start];
				i++;
				spaceFlag = 0; /* Reset the space flag */
			}
			start++;
		}
		str[i] = '\0'; /* Null-terminate the new string */
	}
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

/**
 * _strtok - Tokenizes a string by delimiter
 * @str: The string to be tokenized
 * @delim: The delimiter used for tokenization
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found.
 */
char *_strtok(char *str, const char *delim)
{
	static char *lastToken;
	char *token;

	if (str != NULL)
		lastToken = str; /* Initialize with the beginning of the string */

	/* Find the start of the next token (skipping leading delimiters) */
	while (*lastToken != '\0' && _strchr(delim, *lastToken) != NULL)
		lastToken++;

	if (*lastToken == '\0')
		return (NULL); /* No more tokens left */

	token = lastToken;

	/* Find the end of the token */
	while (*lastToken != '\0' && _strchr(delim, *lastToken) == NULL)
		lastToken++;

	if (*lastToken != '\0')
	{
		*lastToken = '\0'; /* Null-terminate the token */
		lastToken++;	   /* Move to the next character after the delimiter */
	}

	return (token);
}
