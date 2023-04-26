#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>

/* This is the part of the shell that reads/writes buffer */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* This part consist of command chains */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* This is the part that converts characters */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* This part will return 1 if system getline is used */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	"The .simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct list_string - The singly linked list
 * @numba: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct list_string
{
	int numba;
	char *string;
	struct list_string *next;
} list_t;

/**
 *struct pass_info - contains pseudo-arguements to pass into a function,
 *		    allowing uniform prototype for function pointer struct
 *@arg: A string generated from getline containing arguements
 *@argc: The argument count
 *@argv: An array of strings generated from arg
 *@path: A string path for the current command
 *@linecount_flag: If active, counts line of input
 *@line_count: The error count
 *@err_numba: The error code for exit()s
 *@histcount: The history line number count
 *@file_name: The program filename
 *@env: linked list local copy of environs
 *@environ: The custom modified copy of environ from the env
 *@history: The history nodes
 *@alias: The alias nodes
 *@env_changed: active if environ was changed
 *@status: The return status of the last executed command
 *@cmd_buffa: Address of pointer to cmd_buffa, on if chaining
 *@cmd_buffa_type: CMD_type ||, &&, ;
 *@read_fd: the file directory from which to read line input
 */
typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	char *file_name;
	char **environ;
	unsigned int line_count;
	int argc;
	int err_numba;
	int linecount_flag;
	int status;
	int env_changed;
	list_t *env;
	list_t *history;
	list_t *alias;


	char **cmd_buffa; /* pointer to cmd ; chain buffer,  memory mangement */
	int cmd_buffa_type; /* CMD_type ||, &&, ; */
	int read_fd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built_in - This contains a builtin string and it's related functions
 *@type_b: the builtin command flag
 *@function: the function
 */
typedef struct built_in
{
	char *type_b;
	int (*function)(info_t *);
} built_in_table;


/* chimezie_shell_loop.c */
int hsh(info_t *, char **);
int find_built_in(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* chimezie_parser.c */
int a_cmd(info_t *, char *);
char *dupe_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loop_hsh.c */
int loop_hsh(char **);

/* chimezie_errors.c */
void _dputs(char *);
int _dputchar(char);
int _put_fd(char c, int fd);
int _puts_fd(char *str, int fd);

/* chimezie_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begin_with(const char *, const char *);
char *_strcat(char *, char *);

/* chimezie_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* chimezie_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* chimezie_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* chimezie_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* chimezie_memory.c */
int bfree(void **);

/* chimezie_atoi.c */
int inter_active(info_t *);
int is_delim(char, char *);
int _is_alpha(int);
int _atoi(char *);

/* chimezie_errors1.c */
int _err_atoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_numbers(long int, int, int);
void remove_comment(char *);

/* chimezie_builtin.c */
int _my_exit(info_t *);
int _my_cd(info_t *);
int _my_help(info_t *);

/* chimezie_builtin1.c */
int _my_history(info_t *);
int _my_alias(info_t *);

/*chimezie_getline.c */
ssize_t get_input(info_t *);
int _get_line(info_t *, char **, size_t *);
void sig_int_Handler(int);

/* chimezie_getinfo.c */
void clear_infor(info_t *);
void set_infor(info_t *, char **);
void free_infor(info_t *, int);

/* chimezie_environ.c */
char *_get_env(info_t *, const char *);
int _my_env(info_t *);
int _my_set_env(info_t *);
int _my_unset_env(info_t *);
int populates_env_list(info_t *);

/* chimezie_getenv.c */
char **get_environs(info_t *);
int _unset_env(info_t *, char *);
int _set_env(info_t *, char *, char *);

/* chimezie_history.c */
char *get_history_files(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int re_number_history(info_t *info);

/* chimezie_lists.c */
list_t *add_nodes(list_t **, const char *, int);
list_t *add_nodes_end(list_t **, const char *, int);
size_t print_list_string(const list_t *);
int delete_nodes_at_index(list_t **, unsigned int);
void free_lists(list_t **);

/* chimezie_lists1.c */
size_t list_lens(const list_t *);
char **list_to_string(list_t *);
size_t print_lists(const list_t *);
list_t *nodes_starts_with(list_t *, char *, char);
ssize_t get_nodes_index(list_t *, list_t *);

/* chimezie_vars.c */
int d_chain(info_t *, char *, size_t *);
void checks_chain(info_t *, char *, size_t *, size_t, size_t);
int replaces_alias(info_t *);
int replaces_var(info_t *);
int replaces_str(char **, char *);

#endif
