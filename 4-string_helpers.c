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
