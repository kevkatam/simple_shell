#include "main.h"
/**
 * not_found_error - error message for command not found
 * @data: - relevant data
 * Return: Error message
 */
char *not_found_error(mystruct *data)
{
	int l;
	char *error;
	char *str;

	str = itoa(data->counter);
	l = strlen(data->av[0]) + strlen(str);
	l += strlen(data->args[0]) + 16;
	error = malloc(sizeof(char) * (l + 1));

	if (error == 0)
	{
		free(error);
		free(str);
		return (NULL);
	}
	strcpy(error, data->av[0]);
	strcat(error, ": ");
	strcat(error, str);
	strcat(error, ": ");
	strcat(error, data->args[0]);
	strcat(error, ": not found\n");
	strcat(error, "\0");
	free(str);
	return (error);
}
/**
 * exit_shell_error - error message for exit
 * @data: data relevant
 *
 * Return: error message
 */
char *exit_shell_error(mystruct *data)
{
	int l;
	char *error;
	char *str;

	str = itoa(data->counter);
	l = strlen(data->av[0]) + strlen(str);
	l += strlen(data->args[0]) + strlen(data->args[1])  + 23;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(str);
		return (NULL);
	}
	strcpy(error, data->av[0]);
	strcat(error, ": ");
	strcat(error, str);
	strcat(error, ": ");
	strcat(error, data->args[0]);
	strcat(error, ": illegal number: ");
	strcat(error, data->args[1]);
	strcat(error, "\n\0");
	free(str);
	return (error);
}
/**
 * env_error - error msg for env in getenv
 * @data: relevant data
 * Return: error msg
 */
char *env_error(mystruct *data)
{
	int l;
	char *error;
	char *str;
	char *msg;

	str = itoa(data->counter);
	msg = ": Unable to add/remove from environment\n";
	l = strlen(data->av[0] + strlen(str));
	l += strlen(data->args[0]) + strlen(msg) + 4;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(error);
		free(str);
		return (NULL);
	}
	strcpy(error, data->av[0]);
	strcat(error, ": ");
	strcat(error, str);
	strcat(error, ": ");
	strcat(error, data->args[0]);
	strcat(error, msg);
	strcat(error, "\0");
	free(str);

	return (error);
}
/**
 * path_error_126 - error message for path and failure denied permission
 * @data: relevant data
 * Return: error
 */
char *path_error_126(mystruct *data)
{
	int l;
	char *error;
	char *str;

	str = itoa(data->counter);
	l = strlen(data->av[0] + strlen(str));
	l += strlen(data->args[0]) + 24;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(error);
		free(str);
		return (NULL);
	}
	strcpy(error, data->av[0]);
	strcat(error, ": ");
	strcat(error, str);
	strcat(error, ": ");
	strcat(error, data->args[0]);
	strcat(error, ": Permission denied\n");
	strcat(error, "\0");
	free(str);
	return (error);
}
