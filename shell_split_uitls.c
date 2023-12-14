#include "shell.h"

/**
 * shell_splitter - splits command recieved from stdin by ;
 * @input: String gathered from std
 * Return: Parsed strings to be used as commands
 */
char **shell_splitter(char *input)
{
	char **commands;
	char *command;
	int t;
	int buffsize = BUFSIZE;

	if (input[0] == ' ' && input[shell_strlen(input)] == ' ')
		exit(0);
	if (input == NULL)
		return (NULL);
	commands = malloc(sizeof(char *) * buffsize);
	if (!commands)
	{
		free(commands);
		perror("hsh");
		return (NULL);
	}
	command = shell_strtok(input, ";&");
	for (t = 0; command; t++)
	{
		commands[t] = command;
		command = shell_strtok(NULL, ";&");
	}
	commands[t] = NULL;

	return (commands);
}

