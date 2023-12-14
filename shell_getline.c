#include "shell.h"

/**
 * shell_getline - read input from stdio
 * 
 * Return: the input on a buffer
 */
char *shell_getline()
{
	int t, rd, buffsize = BUFSIZE;
	char c = 0, *buffer, *buff;

	buffer = malloc(buffsize);
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	for (t = 0; c != EOF && c != '\n'; t++)
	{
		fflush(stdin);
		rd = read(STDIN_FILENO, &c, 1);
		if (rd == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		buffer[t] = c;
		if (buffer[0] == '\n')
			return (shell_newline(buffer));
		if (t >= buffsize)
		{
			buffer = realloc(buffer, (buffsize + 2));
			if (buffer == NULL)
			{
				free(buffer);
				return (NULL);
			}
		}
	}
	buffer[t] = '\0';
	buff = shell_whitespace(buffer);
	free(buffer);
	shell_remove_hash(buff);
	return (buff);
}

/**
 * shell_newline - Handles newline character input
 * @string: String to be handled
 * 
 * Return: Empty string
 */
char *shell_newline(char *string)
{
	free(string);
	return ("\0");
}

/**
 * shell_whitespace - remove preceeding whitespaces
 * @str: entry to be modified
 * 
 * Return: Returns the modified string
 */
char *shell_whitespace(char *str)
{
	int t, u = 0;
	char *buff;

	buff = malloc(sizeof(char) * (shell_strlen(str) + 1));
	if (buff == NULL)
	{
		free(buff);
		return (NULL);
	}
	for (t = 0; str[t] == ' '; t++)
		;
	for (; str[t + 1] != '\0'; t++)
	{
		buff[u] = str[t];
		u++;
	}
	buff[u] = '\0';
	if (buff[0] == '\0' || buff[0] == '#')
	{
		free(buff);
		return ("\0");
	}
	return (buff);
}

/**
 * shell_remove_hash - removes everything after '#'
 * @buff: input buffer
 * 
 * Return: nothing
 */
void shell_remove_hash(char *buff)
{
	int t;

	for (t = 0; buff[t] != '\0'; t++)
	{
		if (buff[t] == '#' && buff[t - 1] == ' ' && buff[t + 1] == ' ')
		{
			buff[t] = '\0';
		}
	}
}
