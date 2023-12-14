#include "shell.h"

/**
 * shell_help_env - information on the shell by builtin command 'env'
 */
void shell_help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, shell_strlen(msg));
}

/**
 * shell_help_setenv - information on the shell by builtin command 'setenv'
 */
void shell_help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, shell_strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, shell_strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, shell_strlen(msg));
}

/**
 * shell_help_unsetenv - information on the shell builtin command
 * 'unsetenv'
 */
void shell_help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, shell_strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, shell_strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, shell_strlen(msg));
}

/**
 * shell_display_help - display help for builtin commands
 * @cmd: parsed command
 * @st: Status of last command executed
 * 
 * Return: 0 Success
 */
int shell_display_help(char **cmd, __attribute__((unused))int st)
{
	if (!cmd[1])
		shell_help_all();
	else if (shell_strcmp(cmd[1], "alias") == 0)
		shell_help_alias();
	else if (shell_strcmp(cmd[1], "cd") == 0)
		shell_help_cd();
	else if (shell_strcmp(cmd[1], "exit") == 0)
		shell_help_exit();
	else if (shell_strcmp(cmd[1], "env") == 0)
		shell_help_env();
	else if (shell_strcmp(cmd[1], "setenv") == 0)
		shell_help_setenv();
	else if (shell_strcmp(cmd[1], "unsetenv") == 0)
		shell_help_unsetenv();
	else if (shell_strcmp(cmd[1], "help") == 0)
		shell_help_help();
	return (0);
}

