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
	char **argv;
	char *tkn = string_splitter(line, " ");
	int i = 0;

	argv = malloc(sizeof(char *));

	if (argv == NULL)
	{
		fprintf(stderr, "Error: parsing command error\n");
		free_argv(argv);
		return;
	}

	while (tkn != NULL)
	{
		argv[i] = strdup(tkn);
		i++;
		argv = realloc(argv, (i + 1) * sizeof(char *));
		tkn = string_splitter(NULL, " ");
	}

	argv[i] = NULL;

	if (_strcompare(argv[0], "env") == 0 || _strcompare(argv[0], "exit") == 0)
	{
		call_builtinstoexecve(argv);
	}
	else
	{
		call_forktoexecve(argv, path_list);
	}
	free_argv(argv);
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
		if (argv[0][0] == '/')
		{
			fprintf(stderr, "Executing absolute paths: %s\n", argv[0]);
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror(argv[0]);
			}
		}
		else
		{
			fprintf(stderr, "trying to execute: %s\n", argv[0]);
			cmdpath = search_path(path_list, argv[0]);
			if (cmdpath != NULL)
			{
				fprintf(stderr, "Executing cmmd from path: %s\n", cmdpath);
				if (execve(cmdpath, argv, NULL) == -1)
				{
					perror(argv[0]);
				}
				free(cmdpath);
			}
			else
			{
				fprintf(stderr, "%s: command not found\n", argv[0]);
			}
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


/**
 * free_argv - free memory allotment of argector
 * @argv: argument vectot
 *
 * Return: void
 */
void free_argv(char **argv)
{
	size_t i = 0;

	if (argv == NULL)
		return;

	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

