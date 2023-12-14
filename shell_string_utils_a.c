#include "shell.h"

/**
 * shell_putchar - writes the character to stdout
 * @c: character to prin
 * Return: character to standard output
 */
int shell_putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * shell_puts - prints a string
 * @str: pointer to string
 * Return: void
 */
void shell_puts(char *str)
{
	int t;

	for (t = 0; str[t] != '\0'; t++)
	{
		shell_putchar(str[t]);
	}
	shell_putchar('\n');
}

/**
 * shell_strncpy - copies a string
 * @dest: where to copy to
 * @src: where to copy from
 * @n: number of characters to copy
 * Return: copied strings
 */
char *shell_strncpy(char *dest, char *src, int n)
{
	int t = 0;

	while (t < n && *(src + t))
	{
		*(dest + t) = *(src + t);
		t++;
	}
	while (t < n)
	{
		*(dest + t) = '\0';
		t++;
	}
	return (dest);
}

/**
 * shell_strlen - count the length of a string
 * @s: string input
 * Return: length of string
 */
int shell_strlen(char *s)
{
	int t;

	for (t = 0; s[t] != '\0'; t++)
	{
		continue;
	}
	return (t);
}

/**
 * shell_atoi - convert string to a integer
 * @s: string to convert
 * Return: converted integer
 */
int shell_atoi(char *s)
{
	int t = 0, u = 1, v;
	unsigned int n = 0;

	while (s[t] != '\0')
	{
		if (s[t] == '-')
		{
			return (2);
		}
		v = s[t] - '0';

		if (n > 0 && !(v >= 0 && v <= 9))
			break;

		if (v >= 0 && v <= 9)
			n = n * 10 + v;

		t++;
	}
	n *= u;
	return (n);
}

