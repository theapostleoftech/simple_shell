#include "shell.h"

int shell_env(char **argv, char __attribute__((__unused__)) **ptr);
int shell_setenv(char **argv, char __attribute__((__unused__)) **ptr);
int shell_unsetenv(char **argv, char __attribute__((__unused__)) **ptr);

/**
 * shell_env - Prints the current environment.
 * @argv: An array of arguments passed to the shell.
 * @ptr: A double pointer to the beginning of argv.
 * Return: If an error occurs - -1.
 */
int shell_env(char **argv, char __attribute__((__unused__)) **ptr)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], shell_strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)argv;
	return (0);
}

/**
 * shell_setenv - Changes or adds an environmental variable to the PATH.
 * @argv: An array of arguments passed to the shell.
 * @ptr: A double pointer to the beginning of argv.
 * Return: If an error occurs - -1.
 */
int shell_setenv(char **argv, char __attribute__((__unused__)) **ptr)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!argv[0] || !argv[1])
		return (shell_error_file(argv, -1));

	new_value = malloc(_strlen(argv[0]) + 1 + shell_strlen(argv[1]) + 1);
	if (!new_value)
		return (shell_error_file(argv, -1));
	shell_strcpy(new_value, argv[0]);
	shell_strcat(new_value, "=");
	shell_strcat(new_value, argv[1]);

	env_var = _getenv(argv[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (shell_error_file(argv, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * shell_unsetenv - Deletes an environmental variable from the PATH.
 * @argv: An array of arguments passed to the shell.
 * @ptr: A double pointer to the beginning of argv.
 * Return: If an error occurs - -1.
 */
int shell_unsetenv(char **argv, char __attribute__((__unused__)) **ptr)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!argv[0])
		return (shell_error_file(argv, -1));
	env_var = shell_getenv(argv[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (shell_error_file(argv, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}