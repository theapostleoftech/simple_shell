#include "shell.h"

/**
 * sh_strcpy - function that copies a string
 * @dest: destination
 * @src: source
 * Return: destination
 */
char *sh_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * sh_strcat - function that concatenates two strings
 * @dest: first string
 * @src: second string
 * Return: first string + second string
 */
char *sh_strcat(char *dest, char *src)
{
	char *s = dest;

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
	return (s);
}

/**
 * sh_strchr - function that locates character in a string
 * @s: string to be searched
 * @c: character to be located
 * Return: pointer to character
 */
char *sh_strchr(char *s, char c)
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
 * sh_strncmp - function that compares n amount of characters of two strings
 * @s1: first string
 * @s2: second string
 * @n: amount of characters to compare
 * Return: 1 if the strings don't match otherwise 0
 */
int sh_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL)
		return (-1);

	for (i = 0; i < n && s2[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (1);
		}
	}
	return (0);
}

/**
 * sh_strdup - duplicate a string
 * @str: string
 * Return: duplicated string or Null if failed
 */
char *sh_strdup(char *str)
{
	size_t len, i;
	char *str2;

	len = sh_strlen(str);
	str2 = malloc(sizeof(char) * (len + 1));
	if (!str2)
	{
		return (NULL);
	}
	for (i = 0; i <= len; i++)
	{
		str2[i] = str[i];
	}
	return (str2);
}
