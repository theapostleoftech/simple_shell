#include "shell.h"

/**
 * shell_find_delimiter - checks if a character matchs any character
 * @c: character to check
 * @str: string of delimiters
 * 
 * Return: 1 on success, 0 on failure
 */
unsigned int shell_find_delimiter(char c, const char *str)
{
	unsigned int t;

	for (t = 0; str[t] != '\0'; t++)
	{
		if (c == str[t])
			return (1);
	}
	return (0);
}

/**
 * shell_strtok - extracts tokens of a string
 * @str: string
 * @delim: delimiter
 * 
 * Return: pointer to the next token or NULL
 */
char *shell_strtok(char *str, const char *delim)
{
	static char *tokens;
	static char *new_token;
	unsigned int t;

	if (str != NULL)
		new_token = str;
	tokens = new_token;
	if (tokens == NULL)
		return (NULL);
	for (t = 0; tokens[t] != '\0'; t++)
	{
		if (shell_find_delimiter(tokens[t], delim) == 0)
			break;
	}
	if (new_token[t] == '\0' || new_token[t] == '#')
	{
		new_token = NULL;
		return (NULL);
	}
	tokens = new_token + t;
	new_token = tokens;
	for (t = 0; new_token[t] != '\0'; t++)
	{
		if (shell_find_delimiter(new_token[t], delim) == 1)
			break;
	}
	if (new_token[t] == '\0')
		new_token = NULL;
	else
	{
		new_token[t] = '\0';
		new_token = new_token + t + 1;
		if (*new_token == '\0')
			new_token = NULL;
	}
	return (tokens);
}
