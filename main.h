#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"

int _putchar(char c);
void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);

#endif
