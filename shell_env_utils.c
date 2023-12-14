#include "shell.h"

/**
 * shell_create_env - Creates an array of env var
 * @envi: Array to store env var
 */

void shell_create_env(char **envi)
{
	int t;

	for (t = 0; environ[t]; t++)
		envi[t] = shell_strdup(environ[t]);
	envi[t] = NULL;
}

/**
 * shell_free_env - Frees the memory of the env Var
 * @env:  Array of Environment variables
 */
void shell_free_env(char **env)
{
	int t;

	for (t = 0; env[t]; t++)
	{
		free(env[t]);
	}
}
