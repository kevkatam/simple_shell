#include "main.h"
/**
 * _memcpy - copies info between void pointers
 * @newptr: - destination pointer
 * @ptr: source pointer
 * @s: size of the new pointer
 * Return: no return
 */
void _memcpy(void *newptr, const void *ptr, unsigned int s)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < s; i++)
		char_newptr[i] = char_ptr[i];
}
/**
 * _realloc - reallocates a memory block
 * @p: pointer to memory previously allocated
 * @old_s: size in bytes of allocated space p
 * @new_s: new size in bytes of allocated memory block
 * Return: p, if new_s == old_s returns p without changes
 * NULL if malloc fails
 */
void *_realloc(void *p, unsigned int old_s, unsigned int new_s)
{
	void *newp;

	if (p == NULL)
		return (malloc(new_s));
	if (new_s == 0)
	{
		free(p);
		return (NULL);
	}
	if (new_s == old_s)
		return (p);
	newp = malloc(new_s);
	if (newp == NULL)
		return (NULL);
	if (new_s < old_s)
		_memcpy(newp, p, new_s);
	else
		_memcpy(newp, p, old_s);
	free(p);
	return (newp);
}
/**
 * reallocdp - reallocates memory block of a double pointer
 * @p: double pointer to the memory previously allocated
 * @old_s: size in bytes of allocated memory space of p
 * @new_s: size in bytes of new allocated memory block
 * Return:  p, if new_s == old_s returns p without changes
 * NULL if malloc fails
 */
char **reallocdp(char **p, unsigned int old_s, unsigned int new_s)
{
	char **newp;
	unsigned int i;

	if (p == NULL)
		return (malloc(sizeof(char *) * new_s));
	if (new_s == old_s)
		return (p);
	newp = malloc(sizeof(char *) * new_s);
	if (newp == NULL)
		return (NULL);
	for (i = 0; i < old_s; i++)
	{
		newp[i] = p[i];
	}
	free(p);
	return (newp);
}
