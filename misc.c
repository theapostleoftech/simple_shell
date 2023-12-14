#include "shell.h"

/**
 * sh_sh_splitter - function that checks if a character matchs any character
 * @c: character to check
 * @str: string of separatoriters
 * Return: 1 on success, 0 on failure
 */
unsigned int sh_sh_splitter(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * sh_string_splitter - function that extracts tkns of a string
 * @str: string
 * @separator: separatoriter
 * Return: pointer to the next tkn or NULL
 */
char *sh_string_splitter(char *str, const char *separator)
{
	static char *tkns;
	static char *new_tkn;
	unsigned int i;

	if (str != NULL)
		new_tkn = str;
	tkns = new_tkn;
	if (tkns == NULL)
		return (NULL);
	for (i = 0; tkns[i] != '\0'; i++)
	{
		if (sh_sh_splitter(tkns[i], separator) == 0)
			break;
	}
	if (new_tkn[i] == '\0' || new_tkn[i] == '#')
	{
		new_tkn = NULL;
		return (NULL);
	}
	tkns = new_tkn + i;
	new_tkn = tkns;
	for (i = 0; new_tkn[i] != '\0'; i++)
	{
		if (sh_sh_splitter(new_tkn[i], separator) == 1)
			break;
	}
	if (new_tkn[i] == '\0')
		new_tkn = NULL;
	else
	{
		new_tkn[i] = '\0';
		new_tkn = new_tkn + i + 1;
		if (*new_tkn == '\0')
			new_tkn = NULL;
	}
	return (tkns);
}

/**
 * sh_splitter - Separates command recieved from stdin by ;
 * @entry: String gathered from stdin
 * Return: Parsed strings to be used as commands
 */
char **sh_splitter(char *entry)
{
	char **commands;
	char *command;
	int i;
	int buffsize = BUFSIZE;

	if (entry[0] == ' ' && entry[sh_strlen(entry)] == ' ')
		exit(0);
	if (entry == NULL)
		return (NULL);
	commands = malloc(sizeof(char *) * buffsize);
	if (!commands)
	{
		free(commands);
		perror("hsh");
		return (NULL);
	}
	command = sh_string_splitter(entry, ";&");
	for (i = 0; command; i++)
	{
		commands[i] = command;
		command = sh_string_splitter(NULL, ";&");
	}
	commands[i] = NULL;

	return (commands);
}
