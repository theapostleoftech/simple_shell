#include "shell.h"

/**
 * create_path - create path list
 *
 * Return: path list
 */
pathlist *create_path()
{
	char *path = getenv("PATH");
	char *tkn;
	pathlist *list = malloc(sizeof(pathlist));

	if (list == NULL)
		return (NULL);
	list->paths = NULL;
	list->num = 0;
	tkn = string_splitter(path, ":");

	while (tkn != NULL)
	{
		list->paths = realloc(list->paths, sizeof(char *) * (list->num + 1));
		if (list->paths == NULL)
		{
			free(list);
			return (NULL);
		}
		list->paths[list->num] = tkn;
		list->num++;
		tkn = string_splitter(NULL, ":");
	}
	return (list);
}


/**
 * free_path - free memory of path
 * @list: path list
 *
 * Return: void
 */
void free_path(pathlist *list)
{
	int p;

	for (p = 0; p < list->num; p++)
		free(list->paths[p]);
	free(list->paths);
	free(list);
}

/**
 * search_path - search for path
 * @list: path list
 * @ord: command to search in path
 *
 * Return: path
 */
char *search_path(pathlist *list, const char *ord)
{
	int p;
	size_t buffer_sz = 256;
	char *realpath;

	if (list == NULL || ord == NULL)
	{
		fprintf(stderr, "Error: Invalid arguments in search_path\n");
		return (NULL);
	}
	realpath = malloc(buffer_sz);
	if (!realpath)
	{
		perror("Error: Memory allocation failed");
		return (NULL);
	}

	for (p = 0; p < list->num; p++)
	{
		if (snprintf(realpath, buffer_sz, "%s/%s", list->paths[p], ord) >= 0)
		{
			if (access(realpath, F_OK) == 0 && access(realpath, X_OK) == 0)
			{
				return (realpath);
			}
		}
		else
		{
			buffer_sz *= 2;
			free(realpath);
			realpath = malloc(buffer_sz);
			if (!realpath)
			{
				perror("Error: Memory allocation failed");
				return (NULL);
			}
		}
	}
	free(realpath);
	return (NULL);
}

