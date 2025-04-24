#include "main.h"

extern char **environ;

/**
 * main - Entry point of the shell.
 * Return: 0 on success, or exit status.
 */
int main(void)
{
	char *command = NULL;
	char **argv_exec = NULL;
	size_t len = 0;
	pid_t pid;
	int status;
	static int last_status = 0;

	set_sigint_handler();
	while (1)
	{
		prompt();
		if (read_command(&command, &len) == NULL)
	{
		if (feof(stdin))
		{
			free(command);
			free_command_cache();
			exit(0);
		}
		continue;
	}

	argv_exec = parse_command(command);
	if (argv_exec == NULL || argv_exec[0] == NULL)
	{
		free(argv_exec);
		free(command);
		command = NULL;
		continue;
	}

	/* Built-ins */
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
	/* PATH handling */
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
	/* Fork + execve */
	pid_t pid = fork();

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
		perror(argv_exec[0]);
		_exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			last_status = WEXISTATUS(status);
		}
	}
	free(argv_exec);
	free(command);
	command = NULL;
	}
	free_command_cache();
}
