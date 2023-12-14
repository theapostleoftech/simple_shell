#include "shell.h"

/**
 * shell_print_error - Displays error message
 * @input: Input recieved from user
 * @counter: Count of shell loop
 * @argv: Arguments 
 * Return: nothing
 */
void shell_print_error(char *input, int counter, char **argv)
{
	char *er;

	PRINT(argv[0]);
	PRINT(": ");
	er = shell_itoa(counter);
	PRINT(er);
	free(er);
	PRINT(": ");
	PRINT(input);
	PRINT(": not found\n");
}

/**
 *  shell_prerror - Prints custom Error
 * @argv: Arguments
 * @c: Error Count
 * @cmd: Array of parsed command strings
 * Return: nothing
 */
void shell_prerror(char **argv, int c, char **cmd)
{
	char *er = shell_itoa(c);

	PRINT(argv[0]);
	PRINT(": ");
	PRINT(er);
	PRINT(": ");
	PRINT(cmd[0]);
	PRINT(": Illegal number: ");
	PRINT(cmd[1]);
	PRINT("\n");
	free(er);
}

/**
 * shell_error_file - Prints custom Error
 * @argv: Arguments
 * @c: Error Count
 * Return: nothing
 */
void shell_error_file(char **argv, int c)
{
	char *er = shell_itoa(c);

	PRINT(argv[0]);
	PRINT(": ");
	PRINT(er);
	PRINT(": Can't open ");
	PRINT(argv[1]);
	PRINT("\n");
	free(er);
}

