#include "shell.h"
<<<<<<< HEAD

/*
 * Author: Deborah & Nonso
 * Main:  main variable
 *
 */

int main(int ac, char **argv)
{
	char *prompt = "(simple_shell) $ ";
	char *lineptr;
	size_t n = 0;

/* declare void variables */

	(void)ac;
	(void)argv;

	printf("%s", prompt);
	getline(&lineptr, &n, stdin);
	printf("%s\n", lineptr);

	free(lineptr);
	return (0);
=======
/**
 * cmdline_arguments - handle cmdline arguments
 * @arc: argument count
 * @argv: argument vector
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
        while(1)
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
 * @brief 
 * 
 * @return int 
 */
int main(int argc, char *argv[])
{
    cmdline_arguments(argc, argv);

    return (0);

>>>>>>> 4a80745963db0a7ff882c7b5323f88da06ba6a4e
}
