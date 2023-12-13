#include "shell.h"

/**
 * sh_strlen - returns the length of a string
 * @string : string parameter
 *
 * Return: string length.
 */
int sh_strlen(char *string)
{
	int s = 0;
	for (; *string != '\0'; string++)
		s++;
	return (s);
}

/**
 * sh_strcopy - copies the string pointed
 * @end: string to be copied to
 * @org: string to be copied from
 *
 * Return: value of end.
 */
char *sh_strcopy(char *end, char *org)
{
	int t;

	for (t = 0; org[t] != '\0'; t++)
	{
		end[t] = org[t];
	}

	end[t++] = '\0';

	return (end);
}
