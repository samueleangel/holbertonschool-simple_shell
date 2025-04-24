#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024

char *trim_whitespace(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t') str++;
    if (*str == 0) return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n')) end--;

    *(end + 1) = '\0';
    return str;
}

int main(void)
{
    char line[MAX_LINE];
    char *clean_line;
    char *args[64];
    pid_t pid;
    int status;

    while (1)
    {
        int i = 0;

        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL)
        {
            if (feof(stdin))
                break;
            continue;
        }

        clean_line = trim_whitespace(line);

        if (strlen(clean_line) == 0)
            continue;

        args[i] = strtok(clean_line, " ");
        while (args[i] != NULL && i < 63)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid = fork();
        if (pid == 0)
        {
            execvp(args[0], args);
            perror("execvp");
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
