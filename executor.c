#include "shell.h"
/**
 * execute_command - executes a command
 * @line: the command to execute
 * @path_list: path to be executed
 *
 * Return: void
 */
void execute_command(char *line, pathlist *path_list)
{
	char **argv = string_splitter(line, " ");

	if (argv == NULL || argv[0] == NULL)
	{
		fprintf(stderr, "Error: parsing command error\n");
		free(argv);
		return;
	}

	if (_strcompare(argv[0], "env") == 0 || _strcompare(argv[0], "exit") == 0)
	{
		call_builtinstoexecve(argv);
	}
	else
	{
		call_forktoexecve(argv, path_list);
	}
	free(argv);
}

/**
 * call_forktoexecve - calls up and processes
 * @argv: argument vector
 * @path_list: - list to path
 *
 * Return: void
 */
void call_forktoexecve(char **argv, pathlist *path_list)
{
	pid_t s_pid;
	char *cmdpath;
	int notify;

	s_pid = fork();

	if (s_pid == -1)
	{
		perror("Error");
		return;
	}

	if (s_pid == 0)
	{
		cmdpath = search_path(path_list, argv[0]);
		if (cmdpath != NULL)
		{
			if (execve(cmdpath, argv, NULL) == -1)
			{
				perror(argv[0]);
			}
			free(cmdpath);
		}
		else
		{
			fprintf(stderr, "%s: Command not found\n", argv[0]);
		}
		exit(1);
	}
	else
	{
		do {
			waitpid(s_pid, &notify, WUNTRACED);
		} while (!WIFEXITED(notify) && !WIFSIGNALED(notify));
	}
}

/**
 * call_builtinstoexecve - execute builtin commands
 * @argv: argument vector
 *
 * Return: void
 */
void call_builtinstoexecve(char **argv)
{
	if (_strcompare(argv[0], "env") == 0)
	{
		sh_env();
	}
	else if (_strcompare(argv[0], "exit") == 0)
	{
		if (argv[1] != NULL)
		{
			sh_exit(argv[1]);
		}
		else
		{
			sh_exit(NULL);
		}
	}
}

