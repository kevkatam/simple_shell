#include "main.h"
/**
 * readline - reads the input command
 * @i_eof: returns value of getline
 * Return: the input command
 */
char *readline(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
