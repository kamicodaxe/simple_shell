#include "shell.h"
#include <stdio.h>

/**
 * free2D - Frees a 2-dimensional array.
 * @grid: Pointer to the 2D array to be freed.
 */
void free2D(char **grid)
{
	int row;

	if (grid == NULL)
		return;

	for (row = 0; grid[row] != NULL; row++)
	{
		free(grid[row]);
	}

	free(grid);
}

/**
 * printenv - print env variables
 * @env: double pointer to env list
 */
void printenv(char **env)
{
	int i = 0;
	char *newLine = "\n";

	while (env[i] != NULL)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, newLine, 1);
		i++;
	}
}

/**
 * _atoi - converts a string to an integer
 * @s: pointer to the string
 * Return: the converted integer
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	do {
		if (*s == '-')
			sign *= -1;

		else if (*s >= '0' && *s <= '9')
			number = number * 10 + (*s - '0');

		else if (number > 0)
			break;
	} while (*s++);

	return (number * sign);
}
