#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

/**
 * trim_whitespace - Elimina espacios al inicio y final de una cadena
 * @str: Cadena de entrada
 * Return: Puntero a la cadena recortada
 */
char *trim_whitespace(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t' || *str == '\n')
        str++;

    if (*str == '\0')
        return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
        end--;

    *(end + 1) = '\0';

    return str;
}

/**
 * parse_line - Divide una línea en argumentos
 * @line: Línea de entrada
 * @args: Array donde se guardan los argumentos
 */
void parse_line(char *line, char **args)
{
    int i = 0;
    line = trim_whitespace(line);
    args[i] = strtok(line, " \t");
    while (args[i] != NULL && i < MAX_ARGS - 1)
    {
        i++;
        args[i] = strtok(NULL, " \t");
    }
    args[i] = NULL;
}

/**
 * main - Bucle principal de la shell
 */
int main(void)
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL)
        {
            if (feof(stdin))
                break;
            continue;
        }

        char *clean_line = trim_whitespace(line);
        if (strlen(clean_line) == 0)
            continue;

        parse_line(clean_line, args);

        if (args[0] == NULL)
            continue;

        pid = fork();
        if (pid == 0)
        {
            execvp(args[0], args);
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("fork");
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
