#include "main.h"
/**
 * _strdup - duplicates a string in the heap memory
 * @str: type char pointer to string
 * Return: duplicated string
 */
char *_strdup(const char *str)
{
	char *n;
	size_t len;

	len = strlen(str);
	n = malloc(sizeof(char) * (len + 1));
	if (n == NULL)
		return (NULL);
	_memcpy(n, str, len + 1);
	return (n);
}
/**
 * _strlen - returns the lenght of the string
 * @str: pointer
 * Return: length of the string
 */
int _strlen(const char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++)
		;
	return (len);
}
/**
 * _cmpchars - compares characters of string
 * @str: input string
 * @delim: delimiter
 * Return: 1 if are equals, 0 if not
 */
int _cmpchars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
/**
 * _strtok - splits a string by some delimiter
 * @str: input string
 * @delim: delimiter
 * Return: splited string
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *strend;
	char *strstart;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (_cmpchars(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		strend = &str[i];
	}
	strstart = splitted;
	if (strstart == strend)
		return (NULL);
	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != strstart)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == strstart)
					strstart++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (strstart);
}
/**
 * _isdigit - defines if string passed is  number
 * @str: input string
 * Return: 1 if string is a number, 0 otherwise
 */
int _isdigit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}
