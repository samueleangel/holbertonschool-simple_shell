#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

extern char **environ;  /* Declaración explícita para execve */

/* Elimina espacios al inicio y final */
char *trim_spaces(char *str)
{
    while (isspace(*str)) str++;

    if (*str == '\0')
        return str;

    char *end;
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    *(end + 1) = '\0';

    return str;
}

/* Tokeniza la línea de entrada */
void tokenize(char *input, char **args)
{
    int i;
    char *token;
    i = 0;
    token = strtok(input, " \t\r\n");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;
}

int main(void)
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;
    char *clean_line;

    while (1)
    {
        printf("$ ");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            perror("fgets");
            break;
        }

        clean_line = trim_spaces(line);
        if (strlen(clean_line) == 0)
            continue;

        tokenize(clean_line, args);
        if (args[0] == NULL)
            continue;

        pid = fork();
        if (pid == 0)
        {
            execve(args[0], args, environ);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
        }
        else
        {
            perror("fork");
        }
    }

    return 0;
}
