#include "shell.h"

/**
 * find_path - A function that handles PATH
 * @cmd: path to execute command
 *
 * Return: Pointer to the file path, NULL if not found
 */

char *find_path(char *cmd)
{
	char *p;
	char *cpp;
	char *pdir;
	char f_path[MAX_BUF_SIZE];
	int i, j;

	p = _getenv("PATH");
	if (p == NULL)
	{
		perror("_getenv");
		exit(EXIT_FAILURE);
	}

	cpp = _strdup(p); /* copy so original path is not modified */
	if (cpp == NULL)
	{
		perror("_strdup");
		exit(EXIT_FAILURE);
	}

	pdir = _strtok(cpp, ":");

	while (pdir != NULL)
	{
		i = 0;
		while (*pdir != '\0')
		{
			f_path[i++] = *pdir++;
		}
		f_path[i++] = '/';
		j = 0;
		while (cmd[j] != '\0')
		{
			f_path[i++] = cmd[j++];
		}
		f_path[0] = '\0';

		if (access(f_path, X_OK) == 0)
			return (_strdup(f_path));

		pdir = _strtok(NULL, ":");
	}
	return (NULL);
}