#include "shell.h"

/**
 * main - Entry point to program
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Returns condition
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *entry, **cmd, **commands;
	int count = 0, i, condition = 1, stat = 0;

	if (argv[1] != NULL)
		sh_read_file(argv[1], argv);
	signal(SIGINT, sh_signal_to_handle);
	while (condition)
	{
		count++;
		if (isatty(0))
			sh_prompt();
		entry = sh_getline();
		if (entry[0] == '\0')
			continue;
		sh_hist(entry);
		commands = sh_splitter(entry);
		for (i = 0; commands[i] != NULL; i++)
		{
			cmd = sh_cmd_parser(commands[i]);
			if (sh_strcmp(cmd[0], "exit") == 0)
			{
				free(commands);
				sh_exit(cmd, entry, argv, count, stat);
			}
			else if (sh_check_builtin(cmd) == 0)
			{
				stat = sh_handle_builtins(cmd, stat);
				free(cmd);
				continue;
			}
			else
				stat = sh_eva_cmd(cmd, entry, count, argv);
			free(cmd);
		}
		free(entry);
		free(commands);
		wait(&stat);
	}
	return (stat);
}
