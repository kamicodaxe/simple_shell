#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * argcc - argc compute
 * @bytes_read: number of bytes read by getline
 * @line: the string to be executed
 *
 * Return: int argc
 *
 */
int argcc(size_t bytes_read, char *line)
{
	char *token;
	char *line_copy;
	int argc = 0;

	/* Remove leading white spaces */
	trimLeft(line);

	if (line == NULL || *line == '\0' || *line == '\t')
	{
		perror("empty line");
		return (-1);
	}

	/* Check if the last char is \n */
	if (bytes_read > 0 && line[bytes_read - 1] == '\n')
		line[bytes_read - 1] = '\0'; /* line should be null terminated */

	line_copy = malloc(_strlen(line) + 1);
	if (line_copy == NULL)
	{
		perror("line_copy malloc error");
		return (-1);
	}

	_strcpy(line_copy, line);

	token = _strtok(line_copy, " ");
	if (token != NULL)
	{
		argc++;
		token = _strtok(NULL, " ");
	}

	free(line_copy);

	return (argc);
}

/**
 * lineparser - parse the line of command entered by user
 * @bytes_read: number of bytes read by getline
 * @line: the string to be executed
 * @argc: Pointer to argc
 * Return: double pointer
 */
char **lineparser(size_t bytes_read, char *line, int *argc)
{
	char **argv;
	char *token;
	int i = 0;

	*argc = argcc(bytes_read, line);
	if (*argc == -1)
	{
		perror("argc error");
		return (NULL);
	}

	argv = malloc(sizeof(char *) * (*argc + 1));
	if (argv == NULL)
	{
		perror("argv malloc");
		return (NULL);
	}

	token = _strtok(line, " ");
	if (token == NULL)
	{
		perror("empty token");
		return (NULL);
	}

	while (token != NULL)
	{
		argv[i] = malloc(_strlen(token) + 1);
		if (argv[i] == NULL)
		{
			perror("argv malloc");
			return (NULL);
		}
		_strcpy(argv[i], token);
		i++;
		token = _strtok(NULL, " ");
	}
	argv[i] = NULL;

	return (argv);
}

/**
 * execmd - Executes argv array in execve
 * @argv: double pointer to the arguments for execve
 */
void execmd(char **argv)
{

	if ((execve(argv[0], argv, environ)) == -1)
	{
		perror("./shell2");
		exit(EXIT_FAILURE); /* Exit due to execve error */
	}
}

/**
 * main - Entry point of our simple shell
 * Return: 0 if no error, -1 otherwise
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	FILE *stream = stdin;
	ssize_t bytes_read;
	pid_t pid;
	int status;
	char **argv;
	int argc = 0;

	while ((bytes_read = getline(&line, &len, stream)) != -1)
	{
		pid = fork(); /* Create the fork process*/

		if (pid == -1) /* Check fork error*/
		{
			perror("./shell0");
			exit(EXIT_FAILURE); /* Exit due to fork error */
		}

		if (pid == 0)
		{
			argv = lineparser(bytes_read, line, &argc);
			if (argv == NULL)
			{
				perror("argv");
				exit(EXIT_FAILURE);
			}
			execmd(argv); /* Call execmd to execute line */
		}

		if (pid > 0)
		{
			wait(&status); /* Wait for the child process to stop */
		}
	}

	/* Manually free pointer, line */
	free(line);

	return (0); /* Exit with NO_ERRORS! */
}
