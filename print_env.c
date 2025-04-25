#include "main.h"

/**
 * print_env - Imprime environ sin modificaciones
 */
void print_env(void)
{
    char **env = environ;
    size_t len;

    while (*env)
    {
        len = strlen(*env);
        write(STDOUT_FILENO, *env, len);
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}
