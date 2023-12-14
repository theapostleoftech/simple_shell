#include "shell.h"

/**
 * shell_cd - Changes directory
 * @cmd: Parsed command
 * @st: Status of last command executed
 * Return: 0 on success 1
 */
int shell_cd(char **cmd, __attribute__((unused))int st)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		value = chdir(getenv("HOME"));
	else if (shell_strcmp(cmd[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}
	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}

/**
 * s_env - Display enviroment variable
 * @cmd: parsed command
 * @st: status of last command executed
 * Return: Always 0
 */
int s_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int st)
{
	size_t i;
	int len;

	for (t = 0; environ[t] != NULL; t++)
	{
		len = shell_strlen(environ[t]);
		write(1, environ[t], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * shell_show_echo - execute echo cases
 * @st: statue of last command executed
 * @cmd: parsed command
 * Return: Always 1 or execute normal echo
 */
int shell_show_echo(char **cmd, int st)
{
	char *path;
	unsigned int t_pid = getppid();

	if (shell_strncmp(cmd[1], "$?", 2) == 0)
	{
		shell_print_number_int(st);
		PRINT("\n");
	}
	else if (shell_strncmp(cmd[1], "$$", 2) == 0)
	{
		shell_print_number(pid);
		PRINT("\n");
	}
	else if (shell_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = shell_getenv("PATH");
		PRINT(path);
		PRINT("\n");
		free(path);
	}
	else
		return (shell_print_echo(cmd));

	return (1);
}

/**
 * shell_his - display history of user input
 * @c: parsed command
 * @st: status of last command executed
 * Return: 0 success or -1 if fail
 */
int shell_his(__attribute__((unused))char **c, __attribute__((unused))int st)
{
	char *filename = ".shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		er = shell_itoa(counter);
		PRINT(er);
		free(er);
		PRINT(" ");
		PRINT(line);
	}
	if (line)
		free(line);
	fclose(fp);
	return (0);
}
