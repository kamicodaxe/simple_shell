#include "shell.h"

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

	if (line == NULL || *line == '\0' || *line == '\t')
	{
		return (-1);
	}

	/* Check if the last char is \n */
	if (bytes_read > 0 && line[bytes_read - 1] == '\n')
		line[bytes_read - 1] = '\0'; /* line should be null terminated */

	line_copy = _strdup(line);
	if (line_copy == NULL)
	{
		perror("line_copy _strdup error");
		return (-1);
	}

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
		argv[i] = _strdup(token);
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
	char *path;
	char error_msg[] = ": not found\n";

	if (_strcmp(*argv, "env") == 0)
	{
		printenv(env);
		return;
	}

	path = _strdup(find_path(argv[0]));
	if (path == NULL)
	{
		write(STDERR_FILENO, fileName, _strlen(fileName));
		write(STDERR_FILENO, ": 1: ", 5);
		write(STDERR_FILENO, *argv, _strlen(*argv));
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		exit(127);
	}

	argv[0] = path;

	if ((execve(argv[0], argv, env)) == -1)
	{
		perror(fileName);
		exit(127); /* Exit cmd not found */
	}
}

/**
 * processCommand - Process and execute a parsed command.
 * @parsedLine: The parsed command to process and execute.
 * @env: Environmental variables.
 *
 */
void processCommand(char **parsedLine, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(fileName);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		execmd(parsedLine, env);
	}

	if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		{
			free2D(parsedLine);
			free(fileName);
			exit(WEXITSTATUS(status));
		}
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
	size_t len = 0;
	ssize_t bytes_read;
	FILE *stream = stdin;
	char **parsedLine;

	fileName = _strdup(*argv);
	while ((bytes_read = getline(&line, &len, stream)) != -1)
	{
		parsedLine = lineparser(bytes_read, line, &argc);
		if (parsedLine == NULL || parsedLine[0] == NULL || *line == '\n')
			continue;

		if (_strcmp(*parsedLine, "exit") == 0)
		{
			free2D(parsedLine);
			free(line);
			free(fileName);
			_exit(parsedLine[1] ? _atoi(parsedLine[1]) : 0);
		}

		processCommand(parsedLine, env);

		free2D(parsedLine);
	}
	free(fileName);
	free(line);

	return (0); /* Exit with NO_ERRORS! */
}
