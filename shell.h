#ifndef SHELL_H
#define SHELL_H
#define MAX_BUF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _strncmp(char *s1, char *s2, size_t n);
char *_strtok(char *str, const char *delim);
char *_strchr(const char *str, int character);
<<<<<<< HEAD
<<<<<<< HEAD
void trimLeft(char *str);
char *_getenv(const char *envname);
=======
=======
>>>>>>> 7cab1ee536b2a3c7e6a9b3df18d3359be661138f
int _strlen(char *str);
char *_strdup(char *s);
char *_strcpy(char *dest, char *src);
char *_getenv(char *envname);
char *find_path(char *cmd);
<<<<<<< HEAD
>>>>>>> 2bdb86662b19e47341da4dd7117e3fa91e2b4c0e
=======
void trimLeft(char *str);
void free2D(char **grid, int rows);
int _strcmp(char *s1, char *s2);
void printenv(char **env);
char *_getenv(const char *envname);

>>>>>>> 7cab1ee536b2a3c7e6a9b3df18d3359be661138f

#endif
