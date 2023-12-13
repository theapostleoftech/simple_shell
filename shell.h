#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define SHELL_SIGN "$ "
#define RD_SIZE 1024

/**
 * struct pathlist - shell path
 * @paths: paths
 * @num: count of paths
 *
 * Return: path
 */
typedef struct pathlist
{
	char **paths;
	int num;
} pathlist;

extern char **environ;
/*char *custom_getline(void);*/
void execute_command(char *line);
char *my_getline(void);
char **string_splitter(char *string, const char *separator);
void cmdline_arguments(int argc, char *argv[]);
char *search_path(pathlist *list, const char *ord);
void free_path(pathlist *list);
pathlist *create_path();

void sh_exit(char *notify);
void sh_env(void);
int sh_setenv(char *name, char *value, int overwrite);

int _atoint(char *string);
int _strcompare(const char *s1, const char *s2);

#endif
