#include "main.h"
/**
 * execline - finds commands
 * @data: relevant data
 * Return: 1 on success
 */
int execline(mystruct *data)
{
	int (*builtin)(mystruct *data);

	if (data->args[0] == NULL)
		return (1);
	builtin = get_builtin(data->args[0]);
	if (builtin != NULL)
		return (builtin(data));
	return (exec(data));
}
