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
	pathlist *path_list = create_path();
	char *line;
	int i;

	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			execute_command(argv[i], path_list);
		}
	}
	else
	{

		while (1)
		{
			write(1, SHELL_SIGN, strlen(SHELL_SIGN));
			line = my_getline();
			if (line == NULL)
			{
				continue;
			}
			execute_command(line, path_list);
			free(line);
		}
	}
	free(path_list);
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
