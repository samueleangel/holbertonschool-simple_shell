#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define HISTORY_SIZE 100

extern char **command_history;
extern int history_count;

void prompt(void);
char *read_command(char **command, size_t *len);
char **parse_command(char *command);
void set_sigint_handler(void);
void builtin_exit(char **args);
void print_env(void);
void free_command_cache(void);
void add_to_history(char *command);

#endif
