#include "main.h"
/**
 * add_var_node - adds a variable at the end of a var list
 * @h: head of the linked list
 * @lvar: length of the variable
 * @val: value of the variable
 * @lval: lenght of the value
 * Return: address of the head
 */
var *add_var_node(var **h, int lvar, char *val, int lval)
{
	var *n, *temp;

	n = malloc(sizeof(var));
	if (n == NULL)
		return (NULL);
	n->len_var = lvar;
	n->val = val;
	n->len_val = lval;

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
 * free_var_list - frees var list
 * @h: head of the linked list
 * Return: no return
 */
void free_var_list(var **h)
{
	var *temp;
	var *current;

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
