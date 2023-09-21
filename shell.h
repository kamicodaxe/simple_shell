#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _strncmp(char *s1, char *s2, size_t n);
char *_strtok(char *str, const char *delim);
char *_strchr(const char *str, int character);
void trimLeft(char *str);
char *_strcpy(char *dest, char *src);
int _strlen(char *str);
void free2D(char **grid, int rows);
int _strcmp(char *s1, char *s2);
void printenv(char **env);
char *_getenv(const char *envname);

#endif
