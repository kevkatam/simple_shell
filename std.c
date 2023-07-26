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
