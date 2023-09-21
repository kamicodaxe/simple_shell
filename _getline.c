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
 * _skip_whitespace - Skip whitespace characters in the input stream
 * @stream: The input stream
 *
 * Return: 0 if successful, -1 on error or end of file
 */
int _skip_whitespace(FILE *stream)
{
	int ch;

	do {
		ch = _getc(stream->_fileno);

		if (ch == EOF)
		{
			return (-1); /* Error or end of file */
		}
	} while (ch == ' ' || (ch >= '\t' && ch <= '\r') || ch == '\v' || ch == '\f');
	/* Check if whitespace*/

	return (0);
}

/**
 * _realloc_line - Reallocates memory for the line buffer when needed
 * @lineptr: Pointer to the line buffer
 * @n: Pointer to the line buffer size
 * @line_len: Current length of the line
 *
 * Return: 0 if successful, -1 on memory allocation failure
 */
int _realloc_line(char **lineptr, size_t *n, size_t line_len)
{
	char *line = *lineptr;
	size_t line_size = *n;
	char *new_line;

	if (line_len >= line_size - 1)
	{
		line_size *= 2;
		new_line = malloc(line_size);
		if (new_line == NULL)
		{
			free(line);
			return (-1); /* Memory reallocation failed */
		}
		line = new_line;
		*lineptr = line;
		*n = line_size;
	}

	return (0);
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
	char *line;
	size_t line_len = 0;
	int current_char;

	line = *lineptr;
	if (_skip_whitespace(stream) == -1)
		return (-1);

	while (1)
	{
		if (current_char == EOF)
		{
			if (line_len == 0)
			{
				free(line);
				return (-1); /* EOF and no data read */
			}
			break; /* EOF or EOL */
		}

		if (current_char == '\n')
			break; /* End of line */

		if (_realloc_line(lineptr, n, line_len) == -1)
			return (-1);

		line[line_len++] = (char)current_char;
		current_char = _getc(stream->_fileno);
	}

	line[line_len] = '\0';
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
