#include "shell.h"

/**
 * shell_strcpy - copies a string
 * @dest: where to copy to
 * @src: where to copy from 
 * Return: destination
 */
char *shell_strcpy(char *dest, char *src)
{
	int t = 0;

	while (src[t])
	{
		dest[t] = src[t];
		t++;
	}
	dest[t] = '\0';
	return (dest);
}

/**
 * shell_strcat - concatenates two strings
 * @dest: first string
 * @src: second string
 * Return: the two strings
 */
char *shell_strcat(char *dest, char *src)
{
	char *str = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (str);
}

/**
 * shell_strchr - locates character in a string
 * @s: string to be searched
 * @c: character to be located
 * Return: pointer to character
 */
char *shell_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			break;
		}
	} while (*s++);
	return (s);
}

/**
 * shell_strncmp - compares characters of two strings
 * @s1: first string
 * @s2: second string
 * @n: amount of characters to compare
 * Return: 1 if the strings don't match else 0
 */
int shell_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t t;

	if (s1 == NULL)
		return (-1);

	for (t = 0; t < n && s2[t]; t++)
	{
		if (s1[t] != s2[t])
		{
			return (1);
		}
	}
	return (0);
}

/**
 * shell_strdup - duplicate a string
 * @str: string
 * Return: duplicate string or Null if failed
 */
char *shell_strdup(char *str)
{
	size_t len, t;
	char *str2;

	len = shell_strlen(str);
	str2 = malloc(sizeof(char) * (len + 1));
	if (!str2)
	{
		return (NULL);
	}
	for (t = 0; t <= len; t++)
	{
		str2[t] = str[t];
	}
	return (str2);
}

