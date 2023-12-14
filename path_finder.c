#include "shell.h"

/**
 * sh_cmdpath -  Search In $PATH for executable command
 * @cmd: Parsed entry
 * Return: 0 on success or  1 on failure  0
 */
int sh_cmdpath(char **cmd)
{
	char *path, *val, *cmd_path;
	struct stat buf;

	path = sh_getenv("PATH");
	val = sh_string_splitter(path, ":");
	while (val != NULL)
	{
		cmd_path = sh_create_path(*cmd, val);
		if (stat(cmd_path, &buf) == 0)
		{
			*cmd = sh_strdup(cmd_path);
			free(cmd_path);
			free(path);
			return (0);
		}
		free(cmd_path);
		val = sh_string_splitter(NULL, ":");
	}
	free(path);
	free(val);
	return (1);
}

/**
 * sh_create_path - Build command
 * @tkn: Executable command
 * @val: Directory conatining Command
 * Return: Parsed full path of command or NULL if failed
 */
char *sh_create_path(char *tkn, char *val)
{
	char *cmd;
	size_t len;

	len = sh_strlen(val) + sh_strlen(tkn) + 2;
	cmd = malloc(sizeof(char) * len);
	if (cmd == NULL)
	{
		free(cmd);
		return (NULL);
	}

	memset(cmd, 0, len);

	cmd = sh_strcat(cmd, val);
	cmd = sh_strcat(cmd, "/");
	cmd = sh_strcat(cmd, tkn);

	return (cmd);
}

/**
 * sh_getenv - Gets the val of environment variable by name
 * @name: Environment variable name
 * Return: The val of the environment variable or NULL if failed
 */
char *sh_getenv(char *name)
{
	size_t name_len, val_len;
	char *val;
	int i, j, k;

	name_len = sh_strlen(name);
	for (i = 0 ; environ[i]; i++)
	{
		if (sh_strncmp(name, environ[i], name_len) == 0)
		{
			val_len = sh_strlen(environ[i]) - name_len;
			val = malloc(sizeof(char) * val_len);
			if (!val)
			{
				free(val);
				perror("unable to alloc");
				return (NULL);
			}

			j = 0;
			for (k = name_len + 1; environ[i][k]; k++, j++)
			{
				val[j] = environ[i][k];
			}
			val[j] = '\0';

			return (val);
		}
	}
	return (NULL);
}
