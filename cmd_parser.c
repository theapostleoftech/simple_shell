#include "shell.h"

/**
 * sh_cmd_parser - Parses the command recieved from stdin
 * @entry: String gathered from stdin
 * Return: Parsed strings to be used as arguments
 */
char **sh_cmd_parser(char *entry)
{
	char **arguments;
	char *argument;
	int i;
	int buffsize = BUFSIZE;

	if (entry[0] == ' ' && entry[sh_strlen(entry)] == ' ')
		exit(0);
	if (entry == NULL)
		return (NULL);
	arguments = malloc(sizeof(char *) * buffsize);
	if (!arguments)
	{
		free(arguments);
		perror("hsh");
		return (NULL);
	}
	argument = sh_string_splitter(entry, "\n\t\r\a ");
	for (i = 0; argument; i++)
	{
		arguments[i] = argument;
		argument = sh_string_splitter(NULL, "\n\t\r\a ");
	}
	arguments[i] = NULL;

	return (arguments);
}
