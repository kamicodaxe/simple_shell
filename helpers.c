#include "shell.h"
#include <stdio.h>

/**
 * free2D - Frees a 2-dimensional array.
 * @grid: Pointer to the 2D array to be freed.
 * @rows: Number of rows.
 */
void free2D(char **grid, int rows)
{
	int row;

	if (grid == NULL)
		return;

	for (row = 0; row < rows; row++)
		free(grid[row]);

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
