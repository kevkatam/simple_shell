#include "main.h"
/**
 * bringline - assigns line variable for getline
 * @linep: buffer that stores the input string
 * @buffer: string is called to the line
 * @l_size: size of line
 * @b_size: size of buffer
 * Return: 0
 */
void bringline(char **linep, size_t *l_size, char *buffer, size_t b_size)
{
	if (*linep == NULL)
	{
		if (b_size > BUFSIZE)
			*l_size = b_size;
		else
			*l_size = BUFSIZE;
		*linep = buffer;
	}
	else if (*l_size < b_size)
	{
		if (b_size > BUFSIZE)
			*l_size = b_size;
		else
			*l_size = BUFSIZE;
		*linep = buffer;
	}
	else
	{
		strcpy(*linep, buffer);
		free(buffer);
	}
}
/**
 * _getline - reads input from stream
 * @linep: buffer that stores the line
 * @n: size of linep
 * @stream: stream to read from
 * Return: no. of bytes
 */
ssize_t _getline(char **linep, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retv;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;
	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bringline(linep, n, buffer, input);
	retv = input;
	if (i != 0)
		input = 0;
	return (retv);
}
