#include "shell.h"

/**
 * sh_display_error - Displays error message
 * @entry: Input recieved from user
 * @counter: Count of shell loop
 * @argv: Arguments before program starts(argv[0] == Shell Program Name)
 */

void sh_display_error(char *entry, int counter, char **argv)
{
	char *er;

	PRINT(argv[0]);
	PRINT(": ");
	er = _itoa(counter);
	PRINT(er);
	free(er);
	PRINT(": ");
	PRINT(entry);
	PRINT(": not found\n");
}

/**
 *  sh_prerror - Prints custom Error
 * @argv: Arguments before program starts(argv[0] == Shell Program Name)
 * @c: Error Count
 * @cmd: Array of parsed command strings
 */

void sh_prerror(char **argv, int c, char **cmd)
{
	char *er = _itoa(c);

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
 * sh_error_file - Prints custom Error
 * @argv: Arguments before program starts(argv[0] == Shell Program Name)
 * @c: Error Count
 */
void sh_error_file(char **argv, int c)
{
	char *er = _itoa(c);

	PRINT(argv[0]);
	PRINT(": ");
	PRINT(er);
	PRINT(": Can't open ");
	PRINT(argv[1]);
	PRINT("\n");
	free(er);
}
