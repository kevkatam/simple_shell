#include "main.h"
/**
 * get_builtin - built in that pairs with command in arg
 * @cmd: command
 * Return: function pointer of the bult in command
 */
int (*get_builtin(char *cmd))(mystruct *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (strcmp(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].f);
}
