#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t _prompt(void);
char *_strtok(char *str, const char *delim);

#endif
