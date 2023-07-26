#include "main.h"
/**
 * free_mydata - frees mydata structure
 * @data: - data structure
 * Return: no return
 */
void free_mydata(mystruct *data)
{
	unsigned int i;

	for (i = 0; data->_environ[i]; i++)
	{
		free(data->_environ[i]);
	}
	free(data->_environ);
	free(data->pid);
}

/**
 * initialize_data - initializes the mydata structure
 * @data: mydata structure
 * @av: argument vector
 * Return: no return
 */
void initialize_data(mystruct *data, char **av)
{
	unsigned int i;

	data->av = av;
	data->input = NULL;
	data->status = 0;
	data->args = NULL;
	data->counter = 1;

	for (i = 0; environ[i]; i++)
		;
	data->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		data->_environ[i] = strdup(environ[i]);
	}
	data->_environ[i] = NULL;
	data->pid = itoa(getpid());
}

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: Always 0
 */
int main(int ac, char **av)
{
	mystruct data;
	(void) ac;

	signal(SIGINT, getsigint);
	initialize_data(&data, av);
	prompt(&data);
	free_mydata(&data);
	if (data.status > 0)
		return (255);
	return (data.status);
}
