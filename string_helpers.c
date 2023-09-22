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

	if (dest == NULL || src == NULL)
		return (NULL);

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
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
