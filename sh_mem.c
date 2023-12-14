#include "shell.h"

/**
 * sh_realloc -  reallocates a memory block using malloc and free
 *@ptr: pointer
 *@old_size: previous Size Of The Pointer
 *@new_size: new size of the pointer
 *Return: Pointer to reallocated memory
 */
void *sh_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *result;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(new_size);
	if (result == NULL)
	{
		free(result);
		return (NULL);
	}
	if (ptr == NULL)
	{
		fill_an_array(result, '\0', new_size);
		free(ptr);
	}
	else
	{
		sh_memcpy(result, ptr, old_size);
		free(ptr);
	}
	return (result);
}

/**
 * sh_free_all - free memory allocated
 * @cmd: array pointer
 * @line: char pointer
 * Return: Void
 */
void sh_free_all(char **cmd, char *line)
{
	free(cmd);
	free(line);
	cmd = NULL;
	line = NULL;
}

/**
 * sh_memcpy - copy bytes of memory from source to destination
 *@dest: destination pointer
 *@src: source pointer
 *@n: size to be copied
 *Return: pointer to destination
 */
char *sh_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * fill_an_array - fill an array by constant byte
 *@a: void pointer
 *@el: int
 *@len: length for int
 *Return: void pointer
 */
void *fill_an_array(void *a, int el, unsigned int len)
{
	char *p = a;
	unsigned int i = 0;

	while (i < len)
	{
		*p = el;
		p++;
		i++;
	}
	return (a);
}

/**
 * sh_calloc - allocates memory for an array using malloc
 *@size: size
 *Return: void pointer
 */
void *sh_calloc(unsigned int size)
{
	char *a;
	unsigned int i;

	if (size == 0)
		return (NULL);
	a = malloc(size);
	if (a == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		a[i] = '\0';
	}
	return (a);
}
