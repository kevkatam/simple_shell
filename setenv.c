#include "main.h"
/**
 * copyinfo - copies info to create a new env
 * @name: name
 * @value: value
 * Return: new env
 */
char *copyinfo(char *name, char *value)
{
	char *n;
	int lenname, lenvalue, len;

	lenname = _strlen(name);
	lenvalue = _strlen(value);
	len = lenname + lenvalue + 2;
	n = malloc(sizeof(char) * (len));
	strcpy(n, name);
	strcat(n, "=");
	strcat(n, value);
	strcat(n, "\0");

	return (n);
}
/**
 * set_env - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @data: mydata structure
 * Return: no return
 */
void set_env(char *name, char *value, mystruct *data)
{
	int i;
	char *varenv, *nameenv;

	for (i = 0; data->_environ[i]; i++)
	{
		varenv = strdup(data->_environ[i]);
		nameenv = _strtok(varenv, "=");
		if (strcmp(nameenv, name) == 0)
		{
			free(data->_environ[i]);
			data->_environ[i] = copyinfo(nameenv, value);
			free(varenv);
			return;
		}
		free(varenv);
	}
	data->_environ = reallocdp(data->_environ, i, sizeof(char *) * (i + 2));
	data->_environ[i] = copyinfo(name, value);
	data->_environ[i + 1] = NULL;
}
/**
 * _setenv - comparese environment variables names with the name passed
 * @data: relevant data
 * Return: 1 on success
 */
int _setenv(mystruct *data)
{
	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		get_error(data, -1);
		return (1);
	}
	set_env(data->args[1], data->args[2], data);
	return (1);
}
/**
 * _unsetenv - deletes an environment variable
 * @data: relevant data
 * Return: 1 on success
 */
int _unsetenv(mystruct *data)
{
	char **reallocenviron;
	char *varenv, *nameenv;
	int i, j, k;

	if (data->args[1] == NULL)
	{
		get_error(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->_environ[i]; i++)
	{
		varenv = strdup(data->_environ[i]);
		nameenv = _strtok(varenv, "=");
		if (strcmp(nameenv, data->args[1]) == 0)
		{
			k = i;
		}
		free(varenv);
	}
	if (k == -1)
	{
		get_error(data, -1);
		return (1);
	}
	reallocenviron = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->_environ[i]; i++)
	{
		if (i != k)
		{
			reallocenviron[j] = data->_environ[i];
			j++;
		}
	}
	reallocenviron[j] = NULL;
	free(data->_environ[k]);
	free(data->_environ);
	data->_environ = reallocenviron;
	return (1);
}
