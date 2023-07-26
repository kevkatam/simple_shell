#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>
#include <signal.h>
#define BUFSIZE 1024

#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct mydata - sruct containing all relevant data on runtime
 * @av: argument vector
 * @args: tokens of the command line
 * @input: input command line written by user
 * @pid: process ID of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @status: last status of the shell
 */
typedef struct mydata
{
	char **av;
	char **args;
	char *input;
	int counter;
	char **_environ;
	int status;
	char *pid;
} mystruct;
/**
 * struct builtins - builtin struct for commands args
 * @name: name of the command
 * @f: pointer function
 */
typedef struct builtins
{
	char *name;
	int (*f)(mystruct *data);
} builtin_t;
/**
 * struct var_list - single linked list
 * @len_var: lenght of the variable
 * @val: value of the variable
 * @len_val: lenght of the value
 * @next: next node
 * Description: a single linked list tostore variables
 */
typedef struct var_list
{
	int len_var;
	char *val;
	int len_val;
	struct var_list *next;
} var;
/**
 * struct sep_list - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked listnto store separators
 */
typedef struct sep_list
{
	char separator;
	struct sep_list *next;
} seplist;
/**
 * struct line_list - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list
{
	char *line;
	struct line_list *next;
} linelist;

void prompt(mystruct *data);
char *readline(int *i);
void initialize_data(mystruct *data, char **av);
int executable(mystruct *data);
char *not_found_error(mystruct *data);
int get_length(int n);
char *itoa(int n);
char *locate_cmd(char *cmd, char **_environ);
int in_dir(char *path, int *index);
int exec(mystruct *data);
char *exit_shell_error(mystruct *data);
int exit_shell(mystruct *data);
int cmp_env(const char *n_env, const char *name);
int _env(mystruct *data);
int get_error(mystruct *data, int ev);
char *_getenv(const char *name, char **_environ);
int execline(mystruct *data);
int (*get_builtin(char *cmd))(mystruct *);
seplist *add_sep_node_end(seplist **h, char s);
void free_seplist(seplist **h);
linelist *addd_line_node_end(linelist **h, char *line);
void free_linelist(linelist **h);
char *swapchar(char *input, int bool);
void add_node(seplist **heads, linelist **headl, char *input);
void gonext(seplist **lists, linelist **listl, mystruct *data);
int splitcommands(mystruct *data, char *input);
char **splitline(char *input);
void _memcpy(void *newptr, const void *ptr, unsigned int s);
void *_realloc(void *p, unsigned int old_s, unsigned int new_s);
char **reallocdp(char **p, unsigned int old_s, unsigned int new_s);
void getsigint(int s);
char *without_comment(char *in);
int error_check_cmd(char *d, mystruct *data);
char *env_error(mystruct *data);
char *path_error_126(mystruct *data);
void bringline(char **linep, size_t *l_size, char *buffer, size_t b_size);
ssize_t _getline(char **linep, size_t *n, FILE *stream);
int checkvar(var **h, char *in, char *st, mystruct *data);
char *replace_input(var **h, char *input, char *n_input, int nlen);
char *repvar(char *input, mystruct *data);
var *add_var_node(var **h, int lvar, char *val, int lval);
void free_var_list(var **h);
char *_strdup(const char *str);
int _strlen(const char *str);
int _cmpchars(char *str, const char *delim);
char *_strtok(char *str, const char *delim);
int _isdigit(const char *str);
int _atoi(char *str);
char *copyinfo(char *name, char *value);
void set_env(char *name, char *value, mystruct *data);
int _setenv(mystruct *data);
int _unsetenv(mystruct *data);

#endif
