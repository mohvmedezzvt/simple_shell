#ifndef HSH_H
#define HSH_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

#define TOK_BUFSIZE 64
#define TOK_DELIMETER " \t\r\n\a"

extern char **environ;

int hsh_cd(char **args);
int hsh_exit(char **args);
int hsh_env(char **args);
char *hsh_get_PATH(char *name);

void hsh_loop(void);
char *hsh_read_line(void);
char **hsh_parse_line(char *line);
char **hsh_get_path_directories();
int hsh_launch(char **args);
int hsh_num_builtins(void);
int hsh_execute(char **args);

#endif /* HSH_H */
