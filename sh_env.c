#include "shell.h"

/**
 * sh_create_env - Creates an array of Enviroment Variables
 * @envi: Array to store Enviroment Variables
 */

void sh_create_env(char **envi)
{
	int i;

	for (i = 0; environ[i]; i++)
		envi[i] = sh_strdup(environ[i]);
	envi[i] = NULL;
}

/**
 * sh_free_env - Frees the memory of the created Enviroment Variables array
 * @env:  Array of Environment variables
 */
void sh_free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		free(env[i]);
	}
}
