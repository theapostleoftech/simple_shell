#include "shell.h"

/**
 * sh_help_env - Displays information on the shell by builtin command 'env'
 */
void sh_help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, sh_strlen(msg));
}

/**
 * sh_help_setenv - Displays information on the shell by builtin command 'setenv'
 */
void sh_help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, sh_strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, sh_strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, sh_strlen(msg));
}

/**
 * sh_help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'
 */
void sh_help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, sh_strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, sh_strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, sh_strlen(msg));
}

/**
 * display_sh_help - display sh_help for builtin commands
 * @cmd: parsed command
 * @st: Status of last command executed
 * Return: 0 Success
 */
int display_sh_help(char **cmd, __attribute__((unused))int st)
{
	if (!cmd[1])
		sh_help_all();
	else if (sh_strcmp(cmd[1], "alias") == 0)
		sh_help_alias();
	else if (sh_strcmp(cmd[1], "cd") == 0)
		sh_help_cd();
	else if (sh_strcmp(cmd[1], "exit") == 0)
		sh_help_exit();
	else if (sh_strcmp(cmd[1], "env") == 0)
		sh_help_env();
	else if (sh_strcmp(cmd[1], "setenv") == 0)
		sh_help_setenv();
	else if (sh_strcmp(cmd[1], "unsetenv") == 0)
		sh_help_unsetenv();
	else if (sh_strcmp(cmd[1], "sh_help") == 0)
		sh_help_sh_help();
	return (0);
}
