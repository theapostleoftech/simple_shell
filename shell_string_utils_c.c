#include "shell.h"

/**
 * shell_strcmp - compares two string
 * @s1: first string
 * @s2: second strin
 * Return: 0 if identical else how much diffrent
 */
int shell_strcmp(char *s1, char *s2)
{
	int compared = 0, t, len1, len2;

	len1 = shell_strlen(s1);
	len2 = shell_strlen(s2);

	if (s1 == NULL || s2 == NULL)
		return (1);

	if (len1 != len2)
		return (1);

	for (t = 0; s1[t]; t++)
	{
		if (s1[t] != s2[t])
		{
			compared = s1[t] - s2[t];
			break;
		}
		else
			continue;

	}
	return (compared);
}

/**
 * shell_isalpha - check if c is alphabet
 * @c: character to check
 * Return: 1 if true 0 if false
 */
int shell_isalpha(int c)
{
	if (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * shell_itoa - convert integer to character
 * @n: integer to convert
 * Return: character pointer
 */
char *shell_itoa(unsigned int n)
{
	int len = 0, t = 0;
	char *s;

	len = shell_intlen(n);
	s = malloc(len + 2);

	if (!s)
	{
		free(s);
		return (NULL);
	}
	*s = '\0';

	while (n / 10)
	{
		s[t] = (n % 10) + '0';
		n /= 10;
		t++;
	}

	s[t] = (n % 10) + '0';
	shell_array_rev(s, len);
	s[t + 1] = '\0';

	return (s);
}

/**
 * shell_array_rev - reverse an array
 * @arr: array to reverse
 * @len: length of array
 */
void shell_array_rev(char *arr, int len)
{
	int t;
	char temp;

	for (t = 0;  < (len / 2); t++)
	{
		temp = arr[t];
		arr[t] = arr[(len - 1) - t];
		arr[(len - 1) - t] = temp;
	}
}

/**
 * shell_intlen - determine length of integer
 * @num: given integer
 * Return: length of integer
 */
int shell_intlen(int num)
{
	int len = 0;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

