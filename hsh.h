#ifndef HSH_H
#define HSH_H

/* Libraries */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <sys/wait.h>

/* some needs */
#define TOK_BUFSIZE 64
#define TOK_DELIMETER " \t\r\n\a"
extern char **environ;

/* in hsh.c */
void hsh_loop(void);

/* in handlings.c */
char *hsh_read_line(void);
char **hsh_parse_line(char *line);
char **hsh_get_path_directories();
int hsh_launch(char **args);
void excution(char *directories, char **args);

/* in builtins.c */
int hsh_cd(char **args);
int hsh_exit(char **args);
int hsh_env(char **args);
int hsh_setenv(char **args);
int hsh_unsetenv(char **args);

/* in execution.c */
int hsh_num_builtins(void);
int hsh_execute(char **args);

#endif /* HSH_H */
