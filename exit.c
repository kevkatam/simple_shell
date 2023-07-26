#include "main.h"
/**
 * exit_shell - exits the shell
 * @data: relevant data
 * Return: 0 on success
 */
int exit_shell(mystruct *data)
{
	unsigned int u;
	int is_digit, str_len, big_no;

	if (data->args[1] != NULL)
	{
		u = atoi(data->args[1]);
		is_digit = isdigit(data->args[1]);
		str_len = strlen(data->args[1]);
		big_no = u > (unsigned int) INT_MAX;
		if (!is_digit || str_len > 10 || big_no)
		{
			get_error(data, 2);
			data->status = 2;
			return (1);
		}
		data->status = (u % 256);
	}
	return (0);
}
