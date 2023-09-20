#ifndef MAIN_H
#define MAIN_H
#define MAX_BUFF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
void _prompt(void);
int exec(char *cmd);

#endif
