#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

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
 * _realloc_line - Reallocates memory for the line buffer when needed
 * @lineptr: Pointer to the line buffer
 * @n: Pointer to the line buffer size
 * @line_len: Current length of the line
 *
 * Return: 0 if successful, -1 on memory allocation failure
 */
int _realloc_line(char **lineptr, size_t *n, size_t line_len)
{
	size_t new_size, i;
	char *new_line;

	if (line_len >= *n - 1)
	{
		new_size = *n * 2;
		new_line = (char *)malloc(new_size);
		if (new_line == NULL)
		{
			return (-1); /* Memory reallocation failed */
		}
		/* Copy the existing data to the new buffer */
		for (i = 0; i < line_len; i++)
		{
			new_line[i] = (*lineptr)[i];
		}

		free(*lineptr);
		*lineptr = new_line;
		*n = new_size;
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
	char *line = *lineptr;
	size_t line_len = 0;
	int current_char = 0;

	while (1)
	{
		current_char = _getc(stream->_fileno);
		if (current_char == EOF)
		{
			if (line_len == 0)
				return (-1); /* EOF and no data read */
			break;			 /* EOF or EOL */
		}

		if (current_char == '\n')
			break; /* End of line */

		if (line_len >= *n - 1)
		{
			if (_realloc_line(&line, n, line_len) == -1)
				return (-1);
		}

		line[line_len++] = (char)current_char;

		/* Remove white spaces */
		if (line_len == 1 &&
			(current_char == ' ' ||
			 (current_char >= '\t' && current_char <= '\r') ||
			 current_char == '\v' || current_char == '\f'))
		{
			line_len--;
		}
	}

	line[line_len] = '\0';
	*lineptr = line;
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
