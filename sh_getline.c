#include "shell.h"

/**
 * sh_getline - read entry from user
 * Return: the entry on a buffer
 */
char *sh_getline()
{
	int i, rdline, buffer_sz = BUFSIZE;
	char c = 0, *buffer, *buf;

	buffer = malloc(buffer_sz);
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	for (i = 0; c != EOF && c != '\n'; i++)
	{
		fflush(stdin);
		rdline = read(STDIN_FILENO, &c, 1);
		if (rdline == 0)
		{
			free(buffer);
			exit(0);
		}
		buffer[i] = c;
		if (buffer[0] == '\n')
			return (sh_enter_newline(buffer));
		if (i >= buffer_sz)
		{
			buffer = realloc(buffer, (buffer_sz + 2));
			if (buffer == NULL)
			{
				free(buffer);
				return (NULL);
			}
		}
	}
	buffer[i] = '\0';
	buf = sh_rmv_whitespace(buffer);
	free(buffer);
	sh_hash_handler(buf);
	return (buf);
}

/**
 * sh_enter_newline - Handles newline character entry
 * @string: String to be handled
 * Return: Empty string
 */
char *sh_enter_newline(char *string)
{
	free(string);
	return ("\0");
}

/**
 * sh_rmv_whitespace -  remove preceeding whitesh_rmv_whitespaces
 * @str: Input to be modifies
 * Return: Returns the modified string
 */
char *sh_rmv_whitespace(char *str)
{
	int i, j = 0;
	char *buff;

	buff = malloc(sizeof(char) * (sh_strlen(str) + 1));
	if (buff == NULL)
	{
		free(buff);
		return (NULL);
	}
	for (i = 0; str[i] == ' '; i++)
		;
	for (; str[i + 1] != '\0'; i++)
	{
		buff[j] = str[i];
		j++;
	}
	buff[j] = '\0';
	if (buff[0] == '\0' || buff[0] == '#')
	{
		free(buff);
		return ("\0");
	}
	return (buff);
}

/**
 * sh_hash_handler - function that removes everything after '#'
 * @buff: entry buffer
 * Return: nothing
 */
void sh_hash_handler(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
	{
		if (buff[i] == '#' && buff[i - 1] == ' ' && buff[i + 1] == ' ')
		{
			buff[i] = '\0';
		}
	}
}
