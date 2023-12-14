#include "shell.h"

/**
 * shell_parse_cmd - Parses the command recieved from stdin
 * @input: String gathered from stdin
 * 
 * Return: Parsed strings to be used as args
 */
char **shell_parse_cmd(char *input)
{
	char **args;
	char *arg;
	int t;
	int buffsize = BUFSIZE;

	if (input[0] == ' ' && input[shell_strlen(input)] == ' ')
		exit(0);
	if (input == NULL)
		return (NULL);
	args = malloc(sizeof(char *) * buffsize);
	if (!args)
	{
		free(args);
		perror("hsh");
		return (NULL);
	}
	arg = shell_strtok(input, "\n\t\r\a ");
	for (t = 0; arg; t++)
	{
		args[t] = arg;
		arg = shell_strtok(NULL, "\n\t\r\a ");
	}
	args[t] = NULL;

	return (args);
}


/**
 * shell_execute_cmd - Excutes commands
 * @cmd: Array of command strings
 * @input: Input recieved from user
 * @c:Shell Excution Time Case of Command Not Found
 * @argv: Arguments
 * 
 * Return: 1 or 0
 */
int shell_execute_cmd(char **cmd, char *input, int c, char **argv)
{
	int wnotify;
	pid_t s_pid;

	if (*cmd == NULL)
		return (EXIT_FAILURE);
	s_pid = fork();
	if (s_pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (s_pid == 0)
	{
		if (shell_strncmp(*cmd, "./", 2) != 0 && shell_strncmp(*cmd, "/", 1) != 0)
			shell_search_path(cmd);
		if (access(cmd[0], R_OK) != 0)
		{
			shell_print_error(cmd[0], c, argv);
			shell_free_mem(cmd, input);
			exit(127);
		}
		if (execve(*cmd, cmd, environ) == -1)
			return (2);
		else
			return (0);
	}
	wait(&wnotify);
	if (WIFEXITED(wnotify))
	{
		if (WEXITSTATUS(wnotify) == 0)
			return (0);
		else if (WEXITSTATUS(wnotify) == 2)
			return (2);
		else if (WEXITSTATUS(wnotify) == 127)
			return (127);
	}
	return (127);
}

/**
 * signal_to_handle - Configures ^C not to terminate our shell
 * @sig: Incoming Signal
 */
void signal_to_handle(int sig)
{
	if (sig == SIGINT)
	{
		PRINT("\n$ ");
	}
}
