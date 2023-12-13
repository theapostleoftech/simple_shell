#include "shell.h"
/**
 * create_path - create path list
 *
 * Return: path list
 */
pathlist *create_path()
{
	char *path = getenv("PATH");
	char **ptr = string_splitter(path, ":");
	pathlist *list = malloc(sizeof(pathlist));

	list->paths = NULL;
	list->num = 0;
	while (ptr != NULL && *ptr != NULL)
	{
		list->paths = realloc(list->paths, sizeof(char *) * (list->num + 1));
		list->paths[list->num] = strdup(*ptr);
		list->num++;
		ptr = string_splitter(NULL, ":");
	}
	free(ptr);
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
				return (realpath);
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

