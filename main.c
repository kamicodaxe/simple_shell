#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execmd - Executes line string provided
 * @bytes_read: number of bytes read by getline
 * @line: the string to be executed
 */
void execmd(size_t bytes_read, char *line)
{
	char *argv[100];
	int argc = 0;
	char *token;

	/* Check if the last char is \n */
	if (bytes_read > 0 && line[bytes_read - 1] == '\n')
		line[bytes_read - 1] = '\0'; /* line should be null terminated */

	/* Remove leading white spaces */
	trimLeft(line);

	token = _strtok(line, " ");
	if (token == NULL)
		return;

	argv[argc++] = token;
	/* Parse and add arguments */
	while ((token = _strtok(NULL, " ")) != NULL)
	{
		argv[argc++] = token;
		if (argc >= 99)
			return; /* Reached the limit of 100 total arguments */
	}

	argv[argc] = NULL; /* Ensure the argument list is null-terminated */
	if (line == NULL || *line == '\0' || *line == '\t')
	{
		exit(EXIT_SUCCESS);
		return;
	}

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

	while ((bytes_read = getline(&line, &len, stream)) != -1)
	{
		/* Creat the fork process*/
		pid = fork();

		/* Check fork error*/
		if (pid == -1)
		{
			perror("./shell0");
			exit(EXIT_FAILURE); /* Exit due to fork error */
		}

		if (pid == 0)
		{
			/* Call execmd to execute line */
			execmd(bytes_read, line);
			/* Do whatever you want the child process to do here */
		}

		if (pid > 0)
		{
			/* Wait for the child process to stop */
			wait(&status);
			/* Do whatever you want the parent process to do here */
		}
	}

	/* Manually free pointer, line */
	free(line);

	return (0); /* Exit with NO_ERRORS! */
}
