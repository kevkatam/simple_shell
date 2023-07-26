#include "main.h"
/**
 * add_sep_node_end - adds a separator found at the end of sep list
 * @h: head of the linked list
 * @s: separator found
 * Return: address of head
 */
seplist *add_sep_node_end(seplist **h, char s)
{
	seplist *n, *temp;

	n = malloc(sizeof(seplist));
	if (n == NULL)
		return (NULL);
	n->separator = s;
	n->next = NULL;
	temp = *h;

	if (temp == NULL)
	{
		*h = n;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = n;
	}
	return (*h);
}
/**
 * free_seplist - frees a seplist
 * @h: head of the linked list
 * Return: no return
 */
void free_seplist(seplist **h)
{
	seplist *temp;
	seplist *current;

	if (h != NULL)
	{
		current = *h;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*h = NULL;
	}
}
/**
 * add_line_node_end - add command line at the end of a linelist
 * @h: head of the linked list
 * @line: command line
 * Return: address of the head
 */
linelist *addd_line_node_end(linelist **h, char *line)
{
	linelist *n, *temp;

	n = malloc(sizeof(linelist));
	if (n == NULL)
		return (NULL);
	n->line = line;
	n->next = NULL;
	temp = *h;
	if (temp == NULL)
	{
		*h = n;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = n;
	}
	return (*h);
}
/**
 * free_linelist - frees a linelist
 * @h: head of the linked list
 * Return: no return
 */
void free_linelist(linelist **h)
{
	linelist *current, *temp;

	if (h != NULL)
	{
		current = *h;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*h = NULL;
	}
}
