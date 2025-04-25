#include "main.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern char **environ;

/**
 * main - Entry point of the shell.
 * Return: 0 on success, or exit status.
 */
int main(void)
{
	char *command = NULL;
	char **argv_exec = NULL;
	pid_t pid;
	int status;
	static int last_status = 0;

	set_sigint_handler();

	while (1)
	{
		prompt();
		command = read_command();
		if (command == NULL)
		{
			free_command_cache();
			exit(0);
		}

		argv_exec = parse_command(command);
		if (argv_exec == NULL || argv_exec[0] == NULL)
		{
			free(argv_exec);
			free(command);
			command = NULL;
			continue;
		}

		if (strcmp(argv_exec[0], "exit") == 0)
		{
			free(argv_exec);
			free(command);
			_exit(last_status);
		}
		if (strcmp(argv_exec[0], "cd") == 0)
		{
			builtin_cd(argv_exec);
			free(argv_exec);
			free(command);
			command = NULL;
			continue;
		}
		if (strcmp(argv_exec[0], "env") == 0)
		{
			print_env();
			free(argv_exec);
			free(command);
			command = NULL;
			continue;
		}

		if (strchr(argv_exec[0], '/') == NULL)
		{
			char *full_path = find_in_path(argv_exec[0]);
			if (full_path)
			{
				argv_exec[0] = full_path;
			}
			else
			{
				fprintf(stderr, "%s: command not found\n", argv_exec[0]);
				free(argv_exec);
				free(command);
				command = NULL;
				continue;
			}
		}
		else if (access(argv_exec[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: command not found\n", argv_exec[0]);
			free(argv_exec);
			free(command);
			command = NULL;
			continue;
		}

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			free(argv_exec);
			free(command);
			command = NULL;
			continue;
		}

		if (pid == 0)
		{
			execve(argv_exec[0], argv_exec, environ);
			fprintf(stderr, "%s: command not found\n", argv_exec[0]);
			_exit(127);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				last_status = WEXITSTATUS(status);
			}
		}

		free(argv_exec);
		free(command);
		command = NULL;
	}

	free_command_cache();
	return 0;
}
