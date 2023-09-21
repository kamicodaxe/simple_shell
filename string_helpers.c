#include "shell.h"

/**
 * trimLeft - Removes leading white spaces
 * @str: A pointer to the input string
 */
void trimLeft(char *str)
{
	int length = 0;
	int start = 0;

	if (str == NULL)
		return;

	while (str[length] != '\0')
		length++;

	/* Find index of the first non-whitespace character */
	while (
		start < length &&
		(str[start] == ' ' || str[start] == '\t' || str[start] == '\n'))
		start++;

	/* If all leading characters are whitespace, str[start] will be '\0' */
	if (start > 0)
	{
		int i = 0;

		/* Shift the string left to remove leading whitespace */
		while (str[start] != '\0')
		{
			str[i] = str[start];
			i++;
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
