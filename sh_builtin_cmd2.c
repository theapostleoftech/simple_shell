#include "shell.h"

/**
 * sh_check_builtin - Checks if parsed command in built-in
 * @cmd: Parsed command to be check
 * Return: 0 Succes -1 Fail
 */
int sh_check_builtin(char **cmd)
{
	builtin fun[] = {
		{"cd", NULL},
		{"sh_help", NULL},
		{"echo", NULL},
		{"env", NULL},
		{"sh_hist", NULL},
		{NULL, NULL}
	};
	int i = 0;

	if (*cmd == NULL)
	{
		return (-1);
	}
	while ((fun + i)->command)
	{
		if (sh_strcmp(cmd[0], (fun + i)->command) == 0)
			return (0);
		i++;
	}
	return (-1);
}

/**
 * sh_handle_builtins - Handles predefined built in commands
 * @cmd: Array of parsed command strings
 * @st: Status of last execution
 * Return: -1 Failure 0 Success
 */
int sh_handle_builtins(char **cmd, int st)
{
	builtin built_in[] = {
		{"cd", sh_cd},
		{"env", dis_env},
		{"sh_help", display_sh_help},
		{"echo", sh_echo},
		{"sh_hist", sh_hist_dis},
		{NULL, NULL}
	};
	int i = 0;

	while ((built_in + i)->command)
	{
		if (sh_strcmp(cmd[0], (built_in + i)->command) == 0)
		{
			return ((built_in + i)->function(cmd, st));
		}
		i++;
	}
	return (-1);
}

/**
 * sh_exit - Exit Status for built-in commands
 * @cmd: Array of parsed command strings
 * @entry: Input recieved from user (to be freed)
 * @argv: Arguments before program starts(argv[0] == Shell Program Name)
 * @c: Shell execution count
 * @stat: Exit status
 */
void sh_exit(char **cmd, char *entry, char **argv, int c, int stat)
{
	int status, i = 0;

	if (cmd[1] == NULL)
	{
		free(entry);
		free(cmd);
		exit(stat);
	}
	while (cmd[1][i])
	{
		if (sh_isalpha(cmd[1][i++]) != 0)
		{
			sh_prerror(argv, c, cmd);
			free(entry);
			free(cmd);
			exit(2);
		}
		else
		{
			status = sh_atoint(cmd[1]);
			if (status == 2)
			{
				sh_prerror(argv, c, cmd);
				free(entry);
				free(cmd);
				exit(status);
			}
			free(entry);
			free(cmd);
			exit(status);

		}
	}
}
