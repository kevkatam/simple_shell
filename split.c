#include "main.h"
/**
 * swapchar - swaps | and & for non printed chars
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swapchar(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}
/**
 * add_node - adds separators and command lines in the lists
 * @heads: head of separator lists
 * @headl: head of line lists
 * @input: input string
 * Return: no return
 */
void add_node(seplist **heads, linelist **headl, char *input)
{
	int i;
	char *line;

	input = swapchar(input, 0);
	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(heads, input[i]);
		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(heads, input[i]);
			i++;
		}
	}
	line = _strtok(input, ";|&");
	do {
		line = swapchar(line, 1);
		addd_line_node_end(headl, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}
/**
 * gonext - move to the next command line stored
 * @lists: - separator list
 * @listl: command line list
 * @data: mydata structure
 * Return: no return
 */
void gonext(seplist **lists, linelist **listl, mystruct *data)
{
	int loopsep;
	seplist *lss;
	linelist *lsl;

	loopsep = 1;
	lss = *lists;
	lsl = *listl;

	while (lss != NULL && loopsep)
	{
		if (data->status == 0)
		{
			if (lss->separator == '&' || lss->separator == ';')
				loopsep = 0;
			if (lss->separator == '|')
				lsl = lsl->next, lss = lss->next;
		}
		else
		{
			if (lss->separator == '|' || lss->separator == ';')
				loopsep = 0;
			if (lss->separator == '&')
				lsl = lsl->next, lss = lss->next;
		}
		if (lss != NULL && !loopsep)
			lss = lss->next;
	}
	*lists = lss;
	*listl = lsl;
}
/**
 * splitcommands - splits command lines and executes them
 * @data: mydata structure
 * @input: input string
 * Return: 0 to exit 1 to continue
 */
int splitcommands(mystruct *data, char *input)
{
	seplist *heads, *lists;
	linelist *headl, *listl;
	int loop;

	heads = NULL;
	headl = NULL;

	add_node(&heads, &headl, input);

	lists = heads;
	listl = headl;

	while (listl != NULL)
	{
		data->input = listl->line;
		data->args = splitline(data->input);
		loop = execline(data);
		free(data->args);

		if (loop == 0)
			break;
		gonext(&lists, &listl, data);
		if (listl != NULL)
			listl = listl->next;
	}
	free_seplist(&heads);
	free_linelist(&headl);
	if (loop == 0)
		return (0);
	return (1);
}
/**
 * splitline - tokenizes the input string
 * @input: input string
 * Return: splitted input
 */
char **splitline(char *input)
{
	size_t bufsize;
	size_t i;
	char **tokens;
	char *token;

	bufsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bufsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;
	for (i = 1; token != NULL; i++)
	{
		if (i == bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = reallocdp(tokens, i, sizeof(char *) * bufsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL,  TOK_DELIM);
		tokens[i] = token;
	}
	return (tokens);
}
