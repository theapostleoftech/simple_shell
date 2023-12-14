#include "shell.h"

/**
 * shell_prompt - prints '$' to stdout
 * Return: void
 */
void shell_prompt(void)
{
	PRINT("$ ");
}

/**
 * main - Entry point to program
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Returns condition
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *entry, **cmd, **commands;
	int count = 0, t, condition = 1, stat = 0;

	if (argv[1] != NULL)
		shell_read_file(argv[1], argv);
	signal(SIGINT, signal_to_handle);
	while (condition)
	{
		count++;
		if (isatty(STDIN_FILENO))
			shell_prompt();
		entry = shell_getline();
		if (entry[0] == '\0')
			continue;
		history(entry);
		commands = shell_splitter(entry);
		for (t = 0; commands[t] != NULL; t++)
		{
			cmd = shell_parse_cmd(commands[t]);
			if (shell_strcmp(cmd[0], "exit") == 0)
			{
				free(commands);
				shell_exit_cmd(cmd, entry, argv, count, stat);
			}
			else if (shell_check_builtin_cmd(cmd) == 0)
			{
				stat = shell_execute_builtin(cmd, stat);
				free(cmd);
				continue;
			}
			else
				stat = shell_execute_cmd(cmd, entry, count, argv);
			free(cmd);
		}
		free(entry);
		free(commands);
		wait(&stat);
	}
	return (stat);
}

