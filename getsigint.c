#include "main.h"
/**
 * getsigint - handle ctrl + c call in prompt
 * @s: signal handler
 */
void getsigint(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n$ ", 3);
}
