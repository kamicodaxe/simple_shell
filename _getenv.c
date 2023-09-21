#include "shell.h"

/**
 * _getenv - A function that returns the value
 * of the environment variable
 * @envname: pointer to a character constant
 *
 * Return: Pointer to the corresponding value
 * of the env variable, or NULL if not found
 */

char *_getenv(char *envname)
{
	char **env;
	int len;

	if (envname == NULL || environ == NULL || envname[0] == '\0')
		return (NULL);

	len = _strlen(envname);

	for (env = environ; *env != NULL; env++)
	{
		if (_strncmp(*env, envname, len) == 0 && (*env)[len] == '=')
			return (&(*env)[len + 1]); /* Return the value part */
	}
	return (NULL);
}
