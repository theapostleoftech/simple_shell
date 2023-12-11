#include "shell.h"
/**
 * get_input - reads from stream
 *
 * Return: the number of char read
 */
char *get_input(void)
{
	static char buff[B_SIZE];
	char c;
	int n;

	write(1, SHELL_PROMPT, strlen(SHELL_PROMPT));

	while (read(0, &c, 1) > 0 && c != '\n' && n < B_SIZE - 1)
	{
		buff[n++] = c;
	}
	buff[n] = '\0';

	return (buff);

}

/**
 * _get_input - reads form a steam
 * @lineptr: ..
 * @n: ..
 * @stream: ..
 *
 * Return: no of char read
 */
ssize_t _get_input(char **lineptr, size_t *n, FILE *stream)
{
	static 
}

