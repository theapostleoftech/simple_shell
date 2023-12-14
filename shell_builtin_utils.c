#include "shell.h"

/**
 * shell_check_builtin_cmd - Checks if command is in built-in
 * @cmd: Parsed command to be check
 * Return: 0 Succes -1 Fail
 */
int shell_check_builtin_cmd(char **cmd)
{
	builtin fun[] = {
		{"cd", NULL},
		{"help", NULL},
		{"echo", NULL},
		{"env", NULL},
		{"history", NULL},
		{NULL, NULL}
	};
	int i = 0;

	if (*cmd == NULL)
	{
		return (-1);
	}
	while ((fun + i)->command)
	{
		if (shell_strcmp(cmd[0], (fun + i)->command) == 0)
			return (0);
		i++;
	}
	return (-1);
}

/**
 * shell_execute_builtin - Handles predefined built in commands
 * @cmd: Array of parsed command strings
 * @st: Status of last execution
 * Return: -1 Failure 0 Success
 */
int shell_execute_builtin(char **cmd, int st)
{
	builtin built_in[] = {
		{"cd", shell_cd},
		{"env", s_env},
		{"help", shell_display_help},
		{"echo", shell_show_echo},
		{"history", shell_his},
		{NULL, NULL}
	};
	int t = 0;

	while ((built_in + t)->command)
	{
		if (shell_strcmp(cmd[0], (built_in + t)->command) == 0)
		{
			return ((built_in + t)->function(cmd, st));
		}
		t++;
	}
	return (-1);
}

/**
 * shell_exit_cmd - Exit Status for built-in commands
 * @cmd: Array of parsed command strings
 * @input: Input recieved from user
 * @argv: Arguments
 * @c: Shell execution count
 * @stat: Exit status
 */
void shell_exit_cmd(char **cmd, char *input, char **argv, int c, int stat)
{
	int status, t = 0;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(stat);
	}
	while (cmd[1][t])
	{
		if (shell_isalpha(cmd[1][t++]) != 0)
		{
			shell_prerror(argv, c, cmd);
			free(input);
			free(cmd);
			exit(2);
		}
		else
		{
			status = shell_atoi(cmd[1]);
			if (status == 2)
			{
				shell_prerror(argv, c, cmd);
				free(input);
				free(cmd);
				exit(status);
			}
			free(input);
			free(cmd);
			exit(status);

		}
	}
}
