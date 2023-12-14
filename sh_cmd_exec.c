#include "shell.h"

/**
 * sh_eva_cmd - Excutes commands found in predefined path
 * @cmd: Array of parsed command strings
 * @entry: Input recieved from user (to be freed)
 * @c:Shell Excution Time Case of Command Not Found
 * @argv: Arguments before program starts(argv[0] == Shell Program Name)
 * Return: 1 Case Command Null -1 Wrong Command 0 Command Excuted
 */
int sh_eva_cmd(char **cmd, char *entry, int c, char **argv)
{
	int notify;
	pid_t s_pid;

	if (*cmd == NULL)
		return (1);
	s_pid = fork();
	if (s_pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (s_pid == 0)
	{
		if (sh_strncmp(*cmd, "./", 2) != 0 && sh_strncmp(*cmd, "/", 1) != 0)
			sh_cmdpath(cmd);
		if (access(cmd[0], R_OK) != 0)
		{
			sh_display_error(cmd[0], c, argv);
			sh_free_all(cmd, entry);
			exit(127);
		}
		if (execve(*cmd, cmd, environ) == -1)
			return (2);
		else
			return (0);
	}
	wait(&notify);
	if (WIFEXITED(notify))
	{
		if (WEXITSTATUS(notify) == 0)
			return (0);
		else if (WEXITSTATUS(notify) == 2)
			return (2);
		else if (WEXITSTATUS(notify) == 127)
			return (127);
	}
	return (127);
}

/**
 * sh_signal_to_handle - Configures ^C not to terminate our shell
 * @sig: Incoming Signal
 */
void sh_signal_to_handle(int sig)
{
	if (sig == SIGINT)
	{
		PRINT("\n$ ");
	}
}
