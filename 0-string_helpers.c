#include "shell.h"

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

/**
* _strcpy - A function that copies the string pointed
* to by src,including the terminating null byte \0
* to the buffer pointed to by dest.
* @dest: Pointer variable of type char, destination of copy
* @src: Pointer variable of type char, source of copy
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
* _strlen - A function that returns the length of a string.
* @s: string parameter of type char.
*
* Return: Always 0 (Success)
*/

int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0') /* null terminator in C */
	{
		len++;
		s++;
	}
	return (len); /* retun the length of the string */
}
