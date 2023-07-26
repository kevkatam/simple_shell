#include "main.h"
/**
 * get_length - gets the length of a number
 * @n: int number
 * Return: length of the number
 */
int get_length(int n)
{
	unsigned int i;
	int l = 1;

	if (n < 0)
	{
		l++;
		i = n * -1;
	}
	else
	{
		i = n;
	}
	while (i > 9)
	{
		l++;
		i = i / 10;
	}
	return (l);
}
/**
 * itoa - converts int to srtring
 * @n: int number
 * Return: converted string
 */
char *itoa(int n)
{
	unsigned int i;
	int l = get_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (l + 1));
	if (buffer == 0)
		return (NULL);
	*(buffer + l) = '\0';
	if (n < 0)
	{
		i = n * -1;
		buffer[0] = '-';
	}
	else
	{
		i = n;
	}
	l--;
	do {
		*(buffer + l) = (i % 10) + '0';
		i = i / 10;
		l--;
	}
	while (i > 0)
		;
	return (buffer);
}
/**
 * _atoi - converts a string to an integer
 * @str: input strin
 * Return: integer
 */
int _atoi(char *str)
{
	unsigned int count = 0, s = 0, oi = 0, pn = 1, m = 1, i;

	while (*(str + count) != '\0')
	{
		if (s > 0 && (*(str + count) < '0' || *(str + count) > '9'))
			break;
		if (*(str + count) == '-')
			pn *= -1;
		if ((*(str + count) >= '0') && (*(str + count) <= '9'))
		{
			if (s > 0)
				m *= 10;
			s++;
		}
		count++;
	}
	for (i = count - s; i < count; i++)
	{
		oi = oi + ((*(str + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
