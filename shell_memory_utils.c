#include "shell.h"

/**
 * shell_realloc - reallocates a memory block
 * @ptr: pointer
 * @old_size: previous Size Of the ptr
 * @new_size: new size of the ptr
 * Return: ptr to reallocated memory
 */
void *shell_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *output;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	output = malloc(new_size);
	if (output == NULL)
	{
		free(output);
		return (NULL);
	}
	if (ptr == NULL)
	{
		shell_fill_an_array(output, '\0', new_size);
		free(ptr);
	}
	else
	{
		shell_memcpy(output, ptr, old_size);
		free(ptr);
	}
	return (output);
}

/**
 * shell_free_mem - free memory allocated
 * @cmd: array ptr
 * @line: char ptr
 * Return: void
 */
void shell_free_mem(char **cmd, char *line)
{
	free(cmd);
	free(line);
	cmd = NULL;
	line = NULL;
}

/**
 * shell_memcpy - copy bytes of memory
 * @dest: destination ptr
 * @src: source ptr
 * @n: size to be copied
 * Return: ptr to destination
 */
char *shell_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int t;

	for (t = 0; t < n; t++)
	{
		dest[t] = src[t];
	}
	return (dest);
}

/**
 * shell_fill_an_array - fill an array by constant byte
 * @a: void pointer
 * @el: int
 * @len: length of int
 * Return: void ptr
 */
void *shell_fill_an_array(void *a, int el, unsigned int len)
{
	char *p = a;
	unsigned int t = 0;

	while (t < len)
	{
		*p = el;
		p++;
		t++;
	}
	return (a);
}

/**
 * shell_calloc - allocates memory for an array
 * @size: size
 * Return: void pointer
 */
void *shell_calloc(unsigned int size)
{
	char *c;
	unsigned int t;

	if (size == 0)
		return (NULL);
	c = malloc(size);
	if (c == NULL)
		return (NULL);
	for (t = 0; t < size; t++)
	{
		c[t] = '\0';
	}
	return (c);
}

