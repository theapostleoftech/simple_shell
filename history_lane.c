#include "shell.h"

/**
 * sh_hist - write file with user entrys
 * @entry: user entry
 * Return: 0 on success -1 if failed
 */
int sh_hist(char *entry)
{
	char *filename = ".simple_shell_sh_hist";
	ssize_t fd, w;
	int len = 0;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00600);
	if (fd < 0)
		return (-1);
	if (entry)
	{
		while (entry[len])
			len++;
		w = write(fd, entry, len);
		if (w < 0)
			return (-1);
	}
	return (1);
}
