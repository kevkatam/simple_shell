#include "main.h"
/**
 * in_dir - checks if ":" is in the current dircetory
 * @path: poniter of char
 * @index: pointer of index
 * Return: 1 if path is searchabe in currrent directory
 */
int in_dir(char *path, int *index)
{
	if (path[*index] == ':')
		return (1);
	while (path[*index] != ':' && path[*index])
	{
		*index += 1;
	}
	if (path[*index])
		*index += 1;
	return (0);
}


/**
 * locate_cmd - locates a command
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command
 */
char *locate_cmd(char *cmd, char **_environ)
{
	char *path, *p_path, *t_path, *d;
	int len_d, len_cmd, i;
	struct stat t;

	path = _getenv("PATH", _environ);
	if (path)
	{
		p_path = strdup(path);
		len_cmd = strlen(cmd);
		t_path = strtok(p_path, ":");
		i = 0;
		while (t_path != NULL)
		{
			if (in_dir(path, &i))
				if (stat(cmd, &t) == 0)
					return (cmd);
			len_d = strlen(t_path);
			d = malloc(len_d + len_cmd + 2);
			strcpy(d, t_path);
			strcat(d, "/");
			strcat(d, cmd);
			strcat(d, "\0");
			if (stat(d, &t) == 0)
			{
				free(p_path);
				return (d);
			}
			free(d);
			t_path = strtok(NULL, ":");
		}
		free(p_path);
		if (stat(cmd, &t) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &t) == 0)
			return (cmd);
	return (NULL);
}

/**
 * executable - determines if input command is an executable
 * @data: mydata structure
 * Return: 0 if not executable, other number if it is
 */
int executable(mystruct *data)
{
	struct stat t;
	int j;
	char *input;

	input = data->args[0];
	for (j = 0; input[j]; j++)
	{
		if (input[j] == '.')
		{
			if (input[j + 1] == '.')
				return (0);
			if (input[j + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[j] == '/' && j != 0)
		{
			if (input[j] == '.')
				continue;
			j++;
			break;
		}
		else
			break;
	}
	if (j == 0)
		return (0);
	if (stat(input + j, &t) == 0)
	{
		return (j);
	}
	get_error(data, 127);
	return (-1);
}
/**
 * error_check_cmd - checks if the user has permissions to access
 * @d: destination directory
 * @data: mydata structure
 * Return: 1 if there's an error, 0 if not
 */
int error_check_cmd(char *d, mystruct *data)
{
	if (d == NULL)
	{
		get_error(data, 127);
		return (1);
	}
	if (strcmp(data->args[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			get_error(data, 126);
			free(d);
			return (1);
		}
	}
	return (0);
}

/**
 * exec - executes command line
 * @data: data relevant ie input
 * Return: 1 on success
 */
int exec(mystruct *data)
{
	pid_t child_pd;
	int state, exe;
	char *d;

	exe = executable(data);
	if (exe == -1)
	{
		return (1);
	}
	if (exe == 0)
	{
		d = locate_cmd(data->args[0], data->_environ);
		if (error_check_cmd(d, data) == 1)
			return (1);
	}

	child_pd = fork();
	if (child_pd == 0)
	{
		if (exe == 0)
			d = locate_cmd(data->args[0], data->_environ);
		else
			d = data->args[0];
		execve(d + exe, data->args, data->_environ);
	}
	else if (child_pd < 0)
	{
		perror(data->av[0]);
		return (1);
	}
	else
	{
		do {
			waitpid(child_pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	data->status = state / 256;
	return (1);
}
