#include "shell.h"
/**
 * _strcompare - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if equal, 1 if not
 */
int _strcompare(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _atoint - converts a string to an integer
 * @string: string to convert
 *
 * Return: converted integer
 */
int _atoint(char *string)
{
	int output = 0, symb = 1;

	while (*string == ' ' || (*string >= '\t' && *string <= 'r'))
	{
		string++;
	}
	if (*string == '-' || *string == '+')
	{
		symb = (*string == '-') ? -1 : 1;
		string++;
	}

	while (*string >= '0' && *string <= '9')
	{
		output = output * 10 + (*string - '0');
		string++;
	}
	return (output * symb);
}

