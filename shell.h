#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "list.h"

#define USE_GETLINE 0

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUFFER_FLUSH -1

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

extern char **environ;

/**
 * struct Shell_info - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @fd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct Shell_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int fd;
	int histcount;
} Shell_info_t;

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(Shell_info_t *);
} builtin_table;

#define SHELL_INFO_INIT                                                       \
	{                                                                         \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0,     \
			NULL, 0, 0, 0                                                     \
	}

int putchar_error(char c);
void puts_error(char *str);
void print_error(Shell_info_t *info, char *estr);

char *_memset(void *s, char b, unsigned int n);
char *convert_number(long int num, int base, int flags);
int is_delim(char c, char *delim);
int _erratoi(char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _putchar(char c);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
int _strlen(char *s);

int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char **strtow(char *str, char *d);
char *_strchr(char *s, char c);

int is_cmd(Shell_info_t *info, char *path);
char *find_path(Shell_info_t *info, char *pathstr, char *cmd);
char *_strncat(char *dest, char *src, int n);
void sigintHandler(__attribute__((unused)) int sig_num);

int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int build_env_list(Shell_info_t *shell_info);
char *getenv_with_key(Shell_info_t *shell_info, const char *name);
char **get_environ(Shell_info_t *info);
int _setenv(Shell_info_t *info, char *var, char *value);

int replace_alias(Shell_info_t *info);
int replace_vars(Shell_info_t *info);
void remove_comments(char *buf);
int is_chain(Shell_info_t *info, char *buf, size_t *p);
void check_chain(
	Shell_info_t *info, char *buf, size_t *p, size_t i, size_t len);

int read_history(Shell_info_t *shell_info);
int build_history_list(Shell_info_t *info, char *buf, int linecount);
int write_history(Shell_info_t *info);

void clear_info(Shell_info_t *shell_info);
void set_info(Shell_info_t *info, char **av);
void free_info(Shell_info_t *info, int all);

ssize_t get_input(Shell_info_t *shell_info);

int interactive(Shell_info_t *shell_info);
int find_builtin(Shell_info_t *info);
void find_cmd(Shell_info_t *info);

int handle_exit(Shell_info_t *);
int handle_cd(Shell_info_t *);
int handle_help(Shell_info_t *);
int handle_env(Shell_info_t *info);
int handle_history(Shell_info_t *info);

int handle_setenv(Shell_info_t *info);
int handle_unsetenv(Shell_info_t *info);
int handle_alias(Shell_info_t *info);

int shell_run(Shell_info_t *shell_info, char **av);

#endif
