#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

static char *fileName;

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

	trimLeft(line);
	*argc = argcc(bytes_read, line);
	if (*argc == -1)
		return (NULL);

	argv = malloc(sizeof(char *) * (*argc + 1));
	if (argv == NULL)
	{
		perror("argv malloc");
		return (NULL);
	}

	token = _strtok(line, " ");
	if (token == NULL)
		return (NULL); /* Empty token */

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
 * @env: Environmental variables
 */
void execmd(char **argv, char **env)
{

	if (_strcmp(*argv, "env") == 0)
	{
		printenv(env);
		return;
	}

	if ((execve(argv[0], argv, env)) == -1)
	{
		perror(fileName);
		exit(EXIT_FAILURE); /* Exit due to execve error */
	}
}

/**
 * main - Entry point of our simple shell
 * @argc: Argument count
 * @argv: Argument list
 * @env: Environmental variables
 * Return: 0 if no error, -1 otherwise
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t bytes_read, len = 0;
	FILE *stream = stdin;
	pid_t pid;
	int status;

	fileName = malloc(sizeof(*argv) + 1);
	_strcpy(fileName, *argv);
	while ((bytes_read = getline(&line, &len, stream)) != -1)
	{
		argv = lineparser(bytes_read, line, &argc);
		if (argv == NULL)
			continue;

		/* TODO: getPath */
		if (argv[0] == NULL)
			return (0);

		if (_strcmp(*argv, "exit") == 0)
			return (0);

		pid = fork();  /* Create the fork process*/
		if (pid == -1) /* Check fork error*/
		{
			perror(fileName);
			exit(EXIT_FAILURE); /* Exit due to fork error */
		}

		if (pid == 0)
			execmd(argv, env); /* Call execmd to execute line */

		if (pid > 0)
		{
			wait(&status); /* Wait for the child process to stop */
		}
	}
	free(line); /* Manually free pointer, line */
	free(fileName);

	return (0); /* Exit with NO_ERRORS! */
}
