#include "shell.h"
/**
 * sh_exit - exit shell
 * @notify: status
 * Return: void
 */
void sh_exit(char *notify)
{
	int e_notify;

	if (notify != NULL)
	{
		e_notify = atoi(notify);
		exit(e_notify);
	}
	else
	{
		exit(0);
	}
}


/**
 * sh_env - print enviroment
 *
 * Return: void
 */
void sh_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * sh_setenv - set enviroment
 * @name: name of variable
 * @value: value of variable
 * @overwrite: overwrite variable
 *
 * Return: 0 or -1
 */
int sh_setenv(char *name, char *value, int overwrite)
{
	char *var, *nvar;
	size_t name_length, value_length;

	name_length = strlen(name);
	value_length = strlen(value);

	var = getenv(name);
	if (var != NULL && !overwrite)
	{
		fprintf(stderr, "Variable %s already exists\n", name);
		return (-1);
	}
	nvar = malloc(name_length + value_length + 2);
	if (nvar == NULL)
	{
		perror("Error assigning memory");
		return (-1);
	}
	strcpy(nvar, name);
	strcat(nvar, "=");
	strcat(nvar, value);
	if (putenv(nvar) != 0)
	{
		perror("Error assigning variable");
		free(nvar);
		return (-1);
	}
	return (0);
}

/**
 * sh_getenv - Gets env var by name
 * @name: env var name
 *
 * Return: env variable
 */
char *sh_getenv(char *name)
{
	size_t n_length, v_length;
	char *val;
	int m, n, o;

	n_length = strlen(name);
	for (m = 0 ; environ[m]; m++)
	{
		if (strncmp(name, environ[m], n_length) == 0)
		{
			v_length = strlen(environ[m]) - n_length;
			val = malloc(sizeof(char) * v_length);
			if (!val)
			{
				free(val);
				perror("unable to allocate memory");
				return (NULL);
			}

			n = 0;
			for (o = n_length + 1; environ[m][o]; o++, n++)
			{
				val[n] = environ[m][o];
			}
			val[n] = '\0';

			return (val);
		}
	}
	return (NULL);
}