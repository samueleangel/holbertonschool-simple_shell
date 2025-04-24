#include "main.h"

/**
 * main - Entry point for the shell
 *
 * Return: 0 on success, or the exit status of the command on failure
 */
int main(void)
{
    char *command = NULL, **argv_exec;
    size_t len = 0;
    pid_t pid;
    extern char **environ;

    set_sigint_handler();
    while (1)
    {
        prompt();

        if (read_command(&command, &len) == NULL)
        {
            if (read_command(&command, &len) == NULL)
			{
				free(command);
				free_command_cache();
				exit(0);
			}
            continue;
        }

        if (strcmp(command, "exit") == 0)
        {
            free(command);
            free_command_cache();
            builtin_exit(NULL);
        }

        if (command[0] != '\0')
        {
            argv_exec = parse_command(command);

            if (argv_exec == NULL || argv_exec[0] == NULL)
            {
                free(argv_exec);
                free(command);
                command = NULL;
                continue;
            }

            pid = fork();

            if (pid == -1)
            {
                perror("Error");
                free(argv_exec);
                free(command);
                continue;
            }

            if (pid == 0)
            {
                if (execve(argv_exec[0], argv_exec, environ) == -1)
                {
                    perror("./shell");
                    free(argv_exec);
                    free(command);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                wait(NULL);
            }

            free(argv_exec);
        }

        free(command);
        command = NULL;
    }

    free_command_cache();

    return (0);
}
