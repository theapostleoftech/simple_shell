#include "shell.h"
/**
 * my_getline - reads input from the user
 *
 * Return: void
 */
char *my_getline(void)
{
	int n = 0, rd_size;
	char a, *buffer;

	buffer = malloc(RD_SIZE);
<<<<<<< HEAD
	if (!buffer)
		return (NULL);
	while ((rd_size = read(0, &a, 1)) > 0 && a != '\n' && a != -1)
	{
		buffer[n++] = a;
		if (n >= RD_SIZE)
		{
			buffer = realloc(buffer, n + 2);
			if (!buffer)
				return (NULL);
		}
	}
	if (rd_size == 0 && n == 0)
	{
		free(buffer);
		exit(0);
	}
=======

	if (!buffer)
	{
	return (NULL);
	}
	while ((rd_size = read(0, &a, 1)) > 0 && a != '\n' && a != -1)
	{
	buffer[n++] = a;
	if (n >= RD_SIZE)
	{
		buffer = realloc(buffer, n + 2);
	if (!buffer)
		{
		return (NULL);
	}
	}
	}

	if (rd_size == 0 && n == 0)
	{
	free(buffer);
	exit(0);
	}

>>>>>>> ff4b5ceaa26833e2678e0737f35ecce912a469c0
	buffer[n] = '\0';
	return (buffer);
}

