#ifndef SHELL_H
#define SHELL_H

#define PRINT(c) (write(2, c, sh_strlen(c)))
#define BUFFER_SZ 1024
#define SEPARATOR " \t\r\n\a"

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


char *sh_strncpy(char *dest, char *src, int n);
int sh_strlen(char *s);
int sh_putchar(char c);
int sh_atoint(char *s);
void sh_puts(char *str);
int sh_strcmp(char *s1, char *s2);
int sh_isalpha(int c);
void sh_revarr(char *arr, int len);
int sh_intlen(int num);
char *sh_itoa(unsigned int n);
char *sh_strcat(char *dest, char *src);
char *sh_strcpy(char *dest, char *src);
char *sh_strchr(char *s, char c);
int sh_strncmp(const char *s1, const char *s2, size_t n);
char *sh_strdup(char *str);


void sh_free_env(char **env);
void *fill_an_array(void *a, int el, unsigned int len);
char *sh_memcpy(char *dest, char *src, unsigned int n);
void *sh_calloc(unsigned int size);
void *sh_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void sh_free_all(char **entry, char *line);


char *sh_getline();
char *sh_rmv_whitespace(char *str);
char *sh_enter_newline(char *string);
void sh_hash_handler(char *buff);
void sh_prompt(void);
unsigned int sh_sh_splitter(char c, const char *str);
char *sh_string_splitter(char *str, const char *separator);
int sh_hist(char *entry);
char **sh_splitter(char *entry);


void sh_read_file(char *file, char **argv);
void sh_treat_file(char *line, int count, FILE *fp, char **argv);
void sh_exit_for_file(char **cmd, char *line, FILE *fd);

char **sh_cmd_parser(char *entry);
int sh_handle_builtins(char **cmd, int er);
int sh_eva_cmd(char **cmd, char *entry, int c, char **argv);
void sh_signal_to_handle(int sig);

void sh_display_error(char *entry, int counter, char **argv);
void sh_prerror(char **argv, int c, char **cmd);
void sh_error_file(char **argv, int c);

extern char **environ;
void sh_create_env(char **envi);
void sh_free_env(char **env);

void sh_display_number(unsigned int n);
void sh_display_number_int(int n);
int print_echo(char **cmd);

int sh_cmdpath(char **cmd);
char *sh_create_path(char *tkn, char *val);
char *sh_getenv(char *name);

void sh_help_env(void);
void sh_help_setenv(void);
void sh_help_unsetenv(void);
void sh_help_sh_hist(void);
void sh_help_all(void);
void sh_help_alias(void);
void sh_help_cd(void);
void sh_help_exit(void);
void sh_help_sh_help(void);
int display_sh_help(char **cmd, __attribute__((unused))int st);


int sh_check_builtin(char **cmd);
int sh_handle_builtins(char **cmd, int st);
void sh_exit(char **cmd, char *entry, char **argv, int c, int stat);
int sh_cd(char **cmd, __attribute__((unused))int st);
int dis_env(__attribute__((unused)) char **cmd,
	    __attribute__((unused)) int st);
int sh_echo(char **cmd, int st);
int sh_hist_dis(__attribute__((unused))char **c,
		__attribute__((unused)) int st);


/**
 * struct _builtin - Defines a struct that conatins built-in commands
 * with their respective implementation functions
 * @command: - Built-in command
 * @function: - Pointer to custom functions that have
 * similar functionalities as the built-in commands
 */
typedef struct _builtin
{
	char *command;
	int (*function)(char **line, int st);
} builtin;

#endif /*SHELL_H*/
