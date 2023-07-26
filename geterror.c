#include "main.h"
/**
 * get_error - calls the error
 * @data: mydata structure that contains arguments
 * @ev: error value
 * Return: error
 */
int get_error(mystruct *data, int ev)
{
	char *error;

	switch (ev)
	{
	case -1:
		error = env_error(data);
		break;
	case 126:
		error = path_error_126(data);
		break;
	case 127:
		error = not_found_error(data);
		break;
	case 2:
		if (strcmp("exit", data->args[0]) == 0)
			error = exit_shell_error(data);
		break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, strlen(error));
		free(error);
	}
	data->status = ev;
	return (ev);
}
