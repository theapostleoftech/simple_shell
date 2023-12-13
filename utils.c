#include "shell.h"

/**
 * _separator - checks if a character matches another chr
 * @a: char to check
 * @string: string of separator
 *
 * Return: 1 or 0
 */
size_t  _separator(char a, const char *string)
{
	size_t c;

	for (c = 0; string[c] != '\0'; c++)
	{
		if (a == string[c])
		{
			return (1);
		}
	}
	return (0);
}

/**
 * string_splitter - function that splits a string
 * @string: string to split
 * @separator: separates the strings
 *
 * Return: string
 */
char *string_splitter(char *string, const char *separator)
{
	static char *tkns;
	static char *tkn;
	size_t c;

	if (string != NULL)
		tkn = string;

	tkns = tkn;
	if (tkns == NULL)
		return (NULL);

	for (c = 0; tkns[c] != '\0'; c++)
	{
		if (_separator(tkns[c], separator) == 0)
			break;
	}
	if (tkn[c] == '\0' || tkn[c] == '#')
	{
		tkn = NULL;
		return (NULL);
	}
	tkns = tkn + c;
	tkn = tkns;
	for (c = 0; tkn[c] != '\0'; c++)
	{
		if (_separator(tkn[c], separator) == 1)
			break;
	}
	if (tkn[c] == '\0')
		tkn = NULL;
	else
	{
		tkn[c] = '\0';
		tkn = tkn + c + 1;
		if (*tkn == '\0')
			tkn = NULL;
	}
	return (tkns);
}

