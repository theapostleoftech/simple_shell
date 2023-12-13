#include "shell.h"
/**
 * string_splitter - splits a string into tokens
 * @string: string to split
 * @separator: string to split by(delimiter)
 *
 * Return: split string
 */
char **string_splitter(char *string, const char *separator)
{
	static char *buffer;
	char *tkn, char **tkns;
	size_t i = 0;

	if (string != NULL)
		buffer = string;
	if (buffer == NULL)
		return (NULL);
	tkns = malloc(sizeof(char *));
	if (!tkns)
		return (NULL);

			while ((tkn = strtok(buffer, separator)) != NULL)
			{
				buffer = NULL;
				tkns[i] = strdup(tkn);
				if (!tkns[i])
				{
					while (i > 0)
						free(tkns[--i]);
					free(tkns);
					return (NULL);
				}
				i++;
				tkns = realloc(tkns, (i + 1) * sizeof(char *));
				if (!tkns)
				{
					while (i > 0)
						free(tkns[--i]);
					free(tkns);
					return (NULL);
				}
			}
	tkns[i] = NULL;
	return (tkns);
}


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

