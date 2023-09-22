#include "shell.h"

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
