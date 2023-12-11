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

