#include "shell.h"

/**
 * shell_read_file - Reads commands from the argument File
 * @file: File containing commands
 * @argv: Arguments passed 
 * Return: -1 or 0
 */
void shell_read_file(char *file, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int count = 0;

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		shell_error_file(argv, count);
		exit(127);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		count++;
		shell_treat_file(line, count, fp, argv);
	}
	if (line)
		free(line);
	fclose(fp);
	exit(0);
}

/**
 * shell_treat_file - Parse commands and handle their execution
 * @line: Line from file
 * @count: Error counter
 * @fp: File descriptor
 * @argv: Command line arguments
 */
void shell_treat_file(char *line, int count, FILE *fp, char **argv)
{
	char **cmd;
	int stat = 0;

	cmd = shell_parse_cmd(line);
	if (shell_strncmp(cmd[0], "exit", 4) == 0)
		shell_exit_file(cmd, line, fp);
	else if (shell_check_builtin_cmd(cmd) == 0)
	{
		stat = shell_execute_builtin(cmd, stat);
		free(cmd);
	}
	else
	{
		stat = shell_execute_cmd(cmd, line, count, argv);
		free(cmd);
	}
}

/**
 * shell_exit_file - Exit status handler for file input
 * @line: line from a file
 * @cmd: parsed command
 * @fd: file descriptor
 */
void shell_exit_file(char **cmd, char *line, FILE *fd)
{
	int notify;
	int t = 0;

	if (cmd[t] == NULL)
	{
		free(line);
		free(cmd);
		fclose(fd);
		exit(errno);
	}
	while (cmd[1][t])
	{
		if (shell_isalpha(cmd[1][t++]) < 0)
			perror("Illegal number");
	}
	notify = shell_atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(notify);
}

