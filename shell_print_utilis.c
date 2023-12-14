#include "shell.h"

/**
 * shell_print_number - Prints unsigned integers
 * @n: Unsigned integer to be printed
 * 
 * Return: unsigned integer
 */
void shell_print_number(unsigned int n)
{
	unsigned int z = n;

	if ((z / 10) > 0)
		shell_print_number(z / 10);

	shell_putchar(z % 10 + '0');
}

/**
 * shell_print_number_int - Prints integers
 * @n: Integer to be printed
 * 
 * Return: integer
 */
void shell_print_number_int(int n)
{
	unsigned int z = n;

	if (n < 0)
	{
		shell_putchar('-');
		z = -z;
	}
	if ((z / 10) > 0)
		shell_print_number(z / 10);

	shell_putchar(z % 10 + '0');
}

/**
 * shell_print_echo - Executes built-in echo function
 * @cmd: Parsed Command
 * 
 * Return: 0 Upon Success -1 Upon Failure
 */
int shell_print_echo(char **cmd)
{
	pid_t s_pid;
	int notify;

	s_pid = fork();
	if (s_pid == 0)
	{
		if (execve("/bin/echo", cmd, environ) == -1)
		{
			return (-1);
		}
		exit(EXIT_FAILURE);
	}
	else if (s_pid < 0)
	{
		return (-1);
	}
	else
	{
		do {
			waitpid(s_pid, &notify, WUNTRACED);
		} while (!WIFEXITED(notify) && !WIFSIGNALED(notify));
	}
	return (1);
}
