#include "main.h"
/**
 * check_env - checks if the typed variable is an environment variable
 * @h: head of the linked list
 * @in: input string
 * @data: mydata structure
 * Return: no return
 */
void check_env(var **h, char *in, mystruct *data)
{
	int r;
	int ch;
	int j;
	int lval;
	char **envr;

	envr = data->_environ;

	for (r = 0; envr[r]; r++)
	{
		for (j = 1, ch = 0; envr[r][ch]; ch++)
		{
			if (envr[r][ch] == '=')
			{
				lval = strlen(envr[r] + ch + 1);
				add_var_node(h, j, envr[r] + ch + 1, lval);
				return;
			}
			if (in[j] == envr[r][ch])
				j++;
			else
				break;
		}
	}
	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}
	add_var_node(h, j, NULL, 0);
}
/**
 * checkvar - checks if the type variable is $$ or
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the shell
 * @data: mydata structure
 * Return: no return:
 */
int checkvar(var **h, char *in, char *st, mystruct *data)
{
	int i, lst, lpd;

	lst = strlen(st);
	lpd = strlen(data->pid);
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{

			if (in[i + 1] == '?')
				add_var_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}
	return (i);
}
/**
 * replace_input - replaces string into variables
 * @h: head of the linked list
 * @input: input string
 * @n_input: new input string replaced
 * @n_len: new length
 * Return: replaced string
 */
char *replace_input(var **h, char *input, char *n_input, int n_len)
{
	var *index;
	int i, j, k;

	index = *h;
	for (j = i = 0; i < n_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				n_input[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_var; k++)
				{
					n_input[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			n_input[i] = input[j];
			j++;
		}
	}
	return (n_input);
}
/**
 * repvar - calls function to replace string into variables
 * @input: input string
 * @data: mydata structure
 * Return: replaced string
 */
char *repvar(char *input, mystruct *data)
{
	var *h, *index;
	char *status, *n_input;
	int o_len, n_len;

	status = itoa(data->status);
	h = NULL;
	o_len = checkvar(&h, input, status, data);
	if (h == NULL)
	{
		free(status);
		return (input);
	}
	index = h;
	n_len = 0;
	while (index != NULL)
	{
		n_len += (index->len_val - index->len_var);
		index = index->next;
	}
	n_len += o_len;
	n_input = malloc(sizeof(char) * (n_len + 1));
	n_input[n_len] = '\0';
	n_input = replace_input(&h, input, n_input, n_len);
	free(input);
	free(status);
	free_var_list(&h);
	return (n_input);
}
