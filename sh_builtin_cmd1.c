#include "shell.h"

/**
 * sh_cd - Changes directory
 * @cmd: Parsed command
 * @st: Status of last command executed
 * Return: 0 on success 1 if failed (For OLDPWD Always 0 incase of no OLDPWD)
 */
int sh_cd(char **cmd, __attribute__((unused))int st)
{
	int val = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		val = chdir(getenv("HOME"));
	else if (sh_strcmp(cmd[1], "-") == 0)
	{
		val = chdir(getenv("OLDPWD"));
	}
	else
		val = chdir(cmd[1]);

	if (val == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (val != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}

/**
 * dis_env - Display enviroment variable
 * @cmd: parsed command
 * @st: status of last command executed
 * Return: Always 0
 */
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int st)
{
	size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = sh_strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * sh_echo - execute echo cases
 * @st: statue of last command executed
 * @cmd: parsed command
 * Return: Always 1 Or execute normal echo
 */
int sh_echo(char **cmd, int st)
{
	char *path;
	unsigned int pid = getppid();

	if (sh_strncmp(cmd[1], "$?", 2) == 0)
	{
		sh_display_number_int(st);
		PRINT("\n");
	}
	else if (sh_strncmp(cmd[1], "$$", 2) == 0)
	{
		sh_display_number(pid);
		PRINT("\n");
	}
	else if (sh_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = sh_getenv("PATH");
		PRINT(path);
		PRINT("\n");
		free(path);
	}
	else
		return (print_echo(cmd));

	return (1);
}

/**
 * sh_hist_dis - display sh_hist of user entry on simple_shell
 * @c: parsed command
 * @st: status of last command executed
 * Return: 0 success or -1 if fail
 */
int sh_hist_dis(__attribute__((unused))char **c, __attribute__((unused))int st)
{
	char *filename = ".simple_shell_sh_hist";
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
		er = sh_itoa(counter);
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
