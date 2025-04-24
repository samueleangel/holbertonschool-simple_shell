#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1024

/**
 * main - Simple Shell 0.1
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *args[] = {NULL, NULL};
	extern char **environ;

	while (1)
	{
		/* Display prompt */
		printf("#cisfun$ ");
		fflush(stdout);

		/* Read command from user */
		read = getline(&line, &len, stdin);

		/* Handle EOF (Ctrl + D) */
		if (read == -1)
		{
			printf("\n");
			break;
		}

		/* Remove trailing newline */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Ignore empty input */
		if (line[0] == '\0')
			continue;

		args[0] = line;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			/* Child process: attempt to execute the command */
			if (execve(args[0], args, environ) == -1)
			{
				fprintf(stderr, "%s: No such file or directory\n", args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process: wait for child */
			wait(NULL);
		}
	}

	free(line);
	return 0;
}
