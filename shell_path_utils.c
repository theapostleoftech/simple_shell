#include "shell.h"

/**
 * shell_search_path -  Search In $PATH for executable command
 * @cmd: Parsed inpu
 * Return: 0 on success or  1 on failure  0
 */
int shell_search_path(char **cmd)
{
	char *path, *value, *cmd_path;
	struct stat buff;

	path = shell_getenv("PATH");
	value = shell_strtok(path, ":");
	while (value != NULL)
	{
		cmd_path = shell_create_path(*cmd, value);
		if (stat(cmd_path, &buff) == 0)
		{
			*cmd = shell_strdup(cmd_path);
			free(cmd_path);
			free(path);
			return (0);
		}
		free(cmd_path);
		value = shell_strtok(NULL, ":");
	}
	free(path);
	free(value);
	return (1);
}

/**
 * shell_create_path - shell_create_path command
 * @token: Executable command
 * @value: Directory conatining Command
 * Return: Parsed full path of command or NULL if failed
 */
char *shell_create_path(char *token, char *value)
{
	char *cmd;
	size_t len;

	len = shell_strlen(value) + shell_strlen(token) + 2;
	cmd = malloc(sizeof(char) * len);
	if (cmd == NULL)
	{
		free(cmd);
		return (NULL);
	}

	memset(cmd, 0, len);

	cmd = shell_strcat(cmd, value);
	cmd = shell_strcat(cmd, "/");
	cmd = shell_strcat(cmd, token);

	return (cmd);
}

/**
 * shell_getenv - Gets the value of environment variable
 * @name: Environment variable nam
 * Return: value of the environment variable or NULL
 */
char *shell_getenv(char *name)
{
	size_t name_len, value_len;
	char *value;
	int t, u, v;

	name_len = shell_strlen(name);
	for (t = 0 ; environ[t]; t++)
	{
		if (shell_strncmp(name, environ[t], name_len) == 0)
		{
			value_len = shell_strlen(environ[t]) - name_len;
			value = malloc(sizeof(char) * value_len);
			if (!value)
			{
				free(value);
				perror("unable to alloc");
				return (NULL);
			}

			u = 0;
			for (v = name_len + 1; environ[t][v]; v++, u++)
			{
				value[u] = environ[t][v];
			}
			value[u] = '\0';

			return (value);
		}
	}
	return (NULL);
}

