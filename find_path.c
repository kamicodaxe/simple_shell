#include "shell.h"
#include <stdlib.h>

/**
 * find_path - A function that finds the full path of an executable
 * @cmd: The name of the executable file
 *
 * Return: Pointer to the full path, NULL if not found
 */

char *find_path(char *cmd)
{
	char *p;
	char f_path[MAX_BUF_SIZE];

	if (cmd == NULL)
		return (NULL); /* Invalid cmd parameter */

	if (*cmd == '/' || *cmd == '.')
		return (cmd);

	p = _getenv("PATH");

	if (p == NULL)
	{
		return (NULL);
	}

	while (*p)
	{
		int i = 0;

		/* Copy characters from PATH to f_path until a ':' or '\0' is encountered */
		while (*p && *p != ':')
			f_path[i++] = *p++;

		/* Null-terminate the path */
		f_path[i] = '\0';

		/* Append the command name to the path */
		_strcat(f_path, "/");
		_strcat(f_path, cmd);

		/* Check if the path/filename is executable */
		if (access(f_path, X_OK) == 0)
			return (_strdup(f_path)); /* Found the executable */

		if (*p)
			p++; /* Skip the ':' if not at the end of PATH */
	}

	return (NULL); /* Executable not found in any directory */
}
