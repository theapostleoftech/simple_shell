#include "shell.h"

/**
 * sh_read_file - Reads commands from the argument File
 * @file: File containing commands
 * @argv: Arguments passed
 * Return: -1 or 0
 */
void sh_read_file(char *file, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int count = 0;

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		sh_error_file(argv, count);
		exit(127);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		count++;
		sh_treat_file(line, count, fp, argv);
	}
	if (line)
		free(line);
	fclose(fp);
	exit(0);
}

/**
 * sh_treat_file - Parse commands and handle their execution
 * @line: Line from file
 * @count: Error counter
 * @fp: File descriptor
 * @argv: Command line arguments
 */
void sh_treat_file(char *line, int count, FILE *fp, char **argv)
{
	char **cmd;
	int stat = 0;

	cmd = sh_cmd_parser(line);
	if (sh_strncmp(cmd[0], "exit", 4) == 0)
		sh_exit_for_file(cmd, line, fp);
	else if (sh_check_builtin(cmd) == 0)
	{
		stat = sh_handle_builtins(cmd, stat);
		free(cmd);
	}
	else
	{
		stat = sh_eva_cmd(cmd, line, count, argv);
		free(cmd);
	}
}

/**
 * sh_exit_for_file - Exit status handler for file entry
 * @line: Line from a file
 * @cmd: Parsed command
 * @fd: File Descriptor
 */
void sh_exit_for_file(char **cmd, char *line, FILE *fd)
{
	int status;
	int i = 0;

	if (cmd[i] == NULL)
	{
		free(line);
		free(cmd);
		fclose(fd);
		exit(errno);
	}
	while (cmd[1][i])
	{
		if (sh_isalpha(cmd[1][i++]) < 0)
			perror("Illegal number");
	}
	status = sh_atoint(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(status);
}
