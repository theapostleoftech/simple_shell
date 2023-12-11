#include "shell.h"
/**
 * main - main
 *
 * Return: 0
 */
int main()
{
	char *entry;

	while (1)
	{
		entry = get_input();
	}

	free(entry);
	return (0);
}

/*int main()
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("$ ");
	while ((read = _get_input(&line, &len, stdin)) != -1)
	{
		printf("%s\n", line);
		printf("$ ");
	}
	free(line);
	return (0);
}*/

