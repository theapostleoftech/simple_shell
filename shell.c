#include "shell.h"

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
}
