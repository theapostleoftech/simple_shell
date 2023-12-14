#include "shell.h"

/**
 * sh_putchar - function that writes the character to stdout
 * @c: The character to print
 * Return: character to standard output
 */
int sh_putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * sh_puts - function that prints a string
 * @str: pointer to string
 * Return: void
 */
void sh_puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		sh_putchar(str[i]);
	}
	sh_putchar('\n');
}

/**
 * sh_strncpy - function that copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of charaters to be copied
 * Return: copied strings
 */
char *sh_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n && *(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	return (dest);
}

/**
 * sh_strlen - function that counts the length of a string
 * @s: string entry
 * Return: length of string
 */
int sh_strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		continue;
	}
	return (i);
}

/**
 * sh_atoint - function to convert string to a integer
 * @s: string entry
 * Return: converted integer
 */
int sh_atoint(char *s)
{
	int i = 0, j = 1, k;
	unsigned int l = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			return (2);
		}
		k = s[i] - '0';

		if (l > 0 && !(k >= 0 && k <= 9))
			break;

		if (k >= 0 && k <= 9)
			l = l * 10 + k;

		i++;
	}
	l *= j;
	return (l);
}
