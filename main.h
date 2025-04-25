#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define HISTORY_SIZE 100

extern char **command_history;
extern int history_count;
extern char **environ;

/* Prototipos */
void prompt(void);
char *read_command(void);
char **parse_command(char *command);
void set_sigint_handler(void);
void builtin_exit(void);
void builtin_cd(char **args);
void print_env(void);
void free_command_cache(void);
void add_to_history(char *command);
char *find_in_path(char *cmd);
extern int last_status;

#endif
