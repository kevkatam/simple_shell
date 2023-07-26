#include "main.h"
/**
 * without_comment - deletes comment frome the input
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
	int i, upto;

	upto = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				upto = i;
		}
	}
	if (upto != 0)
	{
		in = _realloc(in, i, upto + 1);
		in[upto] = '\0';
	}
	return (in);
}


/**
 * prompt - prints the prompt in a loop
 * @data: relevant data, av, input
 *
 * Return: no return
 */
void prompt(mystruct *data)
{
	int l, i_eof;
	char *input;

	l = 1;
	while (l == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = readline(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;
			input = repvar(input, data);
			l = splitcommands(data, input);
			data->counter += 1;
			free(input);
		}
		else
		{
			l = 0;
			free(input);
		}
	}
}
