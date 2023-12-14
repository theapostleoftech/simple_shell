#ifndef SHELL_H
#define SHELL_H

/***** MACROS *****/
#define PRINT(c) (write(STDERR_FILENO, c, shell_strlen(c)))
#define BUFSIZE 10240
#define DELIMITER " \t\r\n\a"

/*** STANDARD LIBRARIES ***/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/****** SHELL BUILT-IN COMMANDS STRUCT *****/

/**
 * struct _builtin - Defines a struct that conatins built-in commands
 * @command: - Built-in command
 * @function: - Pointer to custom functions that have
 */
typedef struct _builtin
{
	char *command;
	int (*function)(char **line, int st);
} builtin;


/******** STRING UTILITIES **********/

char *shell_strncpy(char *dest, char *src, int n);
int shell_strlen(char *s);
int shell_putchar(char c);
int shell_atoi(char *s);
void shell_puts(char *str);
int shell_strcmp(char *s1, char *s2);
int shell_isalpha(int c);
void shell_array_rev(char *arr, int len);
int shell_intlen(int num);
char *shell_itoa(unsigned int n);
char *shell_strcat(char *dest, char *src);
char *shell_strcpy(char *dest, char *src);
char *shell_strchr(char *s, char c);
int shell_strncmp(const char *s1, const char *s2, size_t n);
char *shell_strdup(char *str);

/*********** SHELL MEMORY UTILITIES ***********/

void shell_free_env(char **env);
void *shell_fill_an_array(void *a, int el, unsigned int len);
char *shell_memcpy(char *dest, char *src, unsigned int n);
void *shell_calloc(unsigned int size);
void *shell_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void shell_free_mem(char **input, char *line);

/****** SHELL MISCELLANEOUS AND INPUT UTILITIES *******/

char *shell_getline();
char *shell_whitespace(char *str);
char *shell_newline(char *string);
void shell_remove_hash(char *buff);
void shell_prompt(void);
unsigned int shell_find_delimiter(char c, const char *str);
char *shell_strtok(char *str, const char *delim);
int history(char *input);
char **shell_splitter(char *input);

/****** SHELL FILE UTILITIES ******/

void shell_read_file(char *file, char **argv);
void shell_treat_file(char *line, int count, FILE *fp, char **argv);
void shell_exit_file(char **cmd, char *line, FILE *fd);

/****** PARSED ARGUMENT HANDLER FUNCTIONS *****/

char **shell_parse_cmd(char *input);
int shell_execute_builtin(char **cmd, int er);
int shell_execute_cmd(char **cmd, char *input, int c, char **argv);
void signal_to_handle(int sig);

/******* ERROR HANDLERS ******/

void shell_print_error(char *input, int counter, char **argv);
void shell_prerror(char **argv, int c, char **cmd);
void shell_error_file(char **argv, int c);

/****** ENVIRONMENT HANDLERS ******/

extern char **environ;
void shell_create_env(char **envi);
void shell_free_env(char **env);

/****** SHELL PRINT UTILITIES *****/

void shell_print_number(unsigned int n);
void shell_print_number_int(int n);
int shell_print_echo(char **cmd);

/******* SHELL PATH UTILITIES *******/

int shell_search_path(char **cmd);
char *shell_create_path(char *token, char *value);
char *shell_getenv(char *name);

/******* HELP HANDLERS *******/

void shell_help_env(void);
void shell_help_setenv(void);
void shell_help_unsetenv(void);
void help_history(void);
void shell_help_all(void);
void shell_help_alias(void);
void shell_help_cd(void);
void shell_help_exit(void);
void shell_help_help(void);
int shell_display_help(char **cmd, __attribute__((unused))int st);

/****** SHELL BUILTIN COMMAND UTILITIES ******/

int shell_check_builtin_cmd(char **cmd);
int shell_execute_builtin(char **cmd, int st);
void shell_exit_cmd(char **cmd, char *input, char **argv, int c, int stat);
int shell_cd(char **cmd, __attribute__((unused))int st);
int s_env(__attribute__((unused)) char **cmd,
	    __attribute__((unused)) int st);
int shell_show_echo(char **cmd, int st);
int shell_his(__attribute__((unused))char **c,
		__attribute__((unused)) int st);

#endif /*SHELL_H*/
