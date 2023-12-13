#include "shell.h"
/**
 * cmdline_arguments - handle cmdline arguments
 * @argc: argument count.
 * @argv: args vector.
 *
 * Return: void
 */
void cmdline_arguments(int argc, char *argv[])
{
	int i;

	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			execute_command(argv[i]);
		}
	}
	else
	{
		char *line;

		while (1)
		{
			write(1, SHELL_SIGN, strlen(SHELL_SIGN));
			line = my_getline();
			if (line == NULL)
			{
				free(line);
				continue;
			}
			execute_command(line);
			free(line);
		}
	}
}



/**
* main - main function
* @argc: arg count
* @argv: arg vetor
*
* Return: 0
*/
int main(int argc, char *argv[])
{
	cmdline_arguments(argc, argv);
	return (0);
}

