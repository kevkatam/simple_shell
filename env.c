#include "main.h"
/**
 * cmp_env - compares env variables names with the name passed
 * @n_env: - name of the env variable
 * @name: name passsed
 * Return: 0 if they are not equal, another value if they are equal
 */
int cmp_env(const char *n_env, const char *name)
{
	int i;

	for (i = 0; n_env[i] != '='; i++)
	{
		if (n_env[i] != name[i])
		{
			return (0);
		}
	}
	return (i + 1);
}
/**
 * _getenv - gets an env variable
 * @name: name of the env variable
 * @_environ: environment variable
 * Return: value of the environment variable if it's found, or NULL if not
 */
char *_getenv(const char *name, char **_environ)
{
	char *p_env;
	int i, mov;

	p_env = NULL;
	mov = 0;
	for (i = 0; _environ[i]; i++)
	{
		mov = cmp_env(_environ[i], name);
		if (mov)
		{
			p_env = _environ[i];
			break;
		}
	}
	return (p_env + mov);
}
/**
 * _env - prints environment variables
 * @data: relevant data
 * Return: 1 on success
 */
int _env(mystruct *data)
{
	int i, j;

	for (i = 0; data->_environ[i]; i++)
	{
		for (j = 0; data->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, data->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->status = 0;
	return (1);
}
