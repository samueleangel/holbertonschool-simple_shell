#include "main.h"
#include <sys/stat.h>

extern char **environ;
char **command_history = NULL;
int history_count = 0;
int last_status = 0;

/**
 * main - Loop principal del shell
 * Return: Siempre 0 (éxito)
 */
int main(void)
{
    char *command = NULL;
    char **args = NULL;

    set_sigint_handler();

    while (1) {
        prompt();  // Usa tu función existente
        
        command = read_command();  // Versión modificada sin realloc
        if (!command) {
            free_command_cache();  // Usa tu función de limpieza
            exit(last_status);
        }

        args = parse_command(command);  // Usa tu parser existente
        if (!args || !args[0]) {
            free(command);
            continue;
        }

        /* Built-ins */
        if (strcmp(args[0], "exit") == 0) {
            free(args);
            free(command);
            builtin_exit();  // Usa tu función existente
        } else if (strcmp(args[0], "cd") == 0) {
            builtin_cd(args);  // Usa tu función existente
        } else if (strcmp(args[0], "env") == 0) {
            print_env();  // Versión corregida abajo
        } else {
            // Ejecución normal (PATH handling con tu find_in_path)
            char *full_path = (strchr(args[0], '/')) ? args[0] : find_in_path(args[0]);
            if (!full_path) {
                fprintf(stderr, "%s: command not found\n", args[0]);
                last_status = 127;
            } else {
                pid_t pid = fork();
                if (pid == 0) {
                    execve(full_path, args, environ);
                    perror(args[0]);
                    _exit(127);
                } else {
                    wait(&last_status);
                }
                if (full_path != args[0]) free(full_path);
            }
        }

        free(args);
        free(command);
    }
    return (0);
}

