#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define READ_SIZE 1024

/**
 * _getc - Custom implementation of getc
 * @fd: File descriptor to read from
 *
 * Return: The next character from fd or EOF on error or end of file
 */
int _getc(int fd)
{
	char ch;
	ssize_t bytes_read = read(fd, &ch, 1);

	if (bytes_read < 0)
	{
		return (EOF);
	}
	else if (bytes_read == 0)
	{
		return (EOF);
	}

	return ((int)ch);
}

/**
 * _readline - Reads a line of from FILE stream
 * @lineptr: Pointer to the line buffer
 * @n: Pointer to the line buffer size
 * @stream: The input stream
 *
 * Return: The number of characters read, -1 on failure
 */
ssize_t _readline(char **lineptr, size_t *n, FILE *stream)
{
	char *line, *new_line;
	size_t line_size = *n, line_len = 0;
	int current_char;

	line = *lineptr;
	while (1)
	{
		current_char = _getc(stream->_fileno);
		if (current_char == EOF)
		{
			if (line_len == 0)
			{
				free(line);
				return (-1); /* EOF and no data read */
			}
			break; /* EOF or EOL */
		}

		if (line_len >= line_size - 1)
		{
			line_size *= 2;
			new_line = malloc(sizeof(line));
			if (new_line == NULL)
			{
				free(line);
				return (-1); /* Memory reallocation failed */
			}
			line = new_line;
			*lineptr = line;
			*n = line_size;
		}

		line[line_len++] = (char)current_char;

		if (current_char == '\n')
			break; /* End of line */
	}

	line[line_len] = '\0'; /* Null-terminate the line */
	return ((ssize_t)line_len);
}

/**
 * _getline - Custom implementation of getline
 * @lineptr: Pointer to the line buffer
 * @n: Pointer to the line buffer size
 * @stream: The input stream
 *
 * Return: The number of characters read, -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (*lineptr == NULL || *n == 0)
	{
		*n = READ_SIZE;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}

	return (_readline(lineptr, n, stream));
}
