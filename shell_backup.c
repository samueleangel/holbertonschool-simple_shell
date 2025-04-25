#include "main.h"
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - Shell entry point
 * Return: Exit status
 */
int main(void)
{
	char *command = NULL;
	char **argv_exec = NULL;
	pid_t pid;
	int status;
	static int last_status = 0;
	char *full_path = NULL;
	int should_free_command = 1; /* Bandera para controlar liberación */

	set_sigint_handler();

	while (1)
	{
		prompt();
		command = read_command();
		if (command == NULL)
		{
			free_command_cache();
			exit(last_status);
		}

		argv_exec = parse_command(command);
		if (argv_exec == NULL || argv_exec[0] == NULL)
		{
			free(argv_exec);
			free(command);
			continue;
		}

		/* Built-in commands */
		if (strcmp(argv_exec[0], "exit") == 0)
		{
			free(argv_exec);
			free(command);
			exit(last_status);
		}
		if (strcmp(argv_exec[0], "cd") == 0)
		{
			builtin_cd(argv_exec);
			free(argv_exec);
			free(command);
			continue;
		}
		if (strcmp(argv_exec[0], "env") == 0)
		{
			print_env();
			free(argv_exec);
			free(command);
			continue;
		}

		/* PATH handling */
		if (strchr(argv_exec[0], '/') == NULL)
		{
			full_path = find_in_path(argv_exec[0]);
			if (full_path == NULL)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", argv_exec[0]);
				last_status = 127;
				free(argv_exec);
				free(command);
				continue;
			}
			/* No liberamos argv_exec[0] aquí, se libera con command */
			argv_exec[0] = full_path;
			should_free_command = 0; /* Evitar doble free */
		}
		else if (access(argv_exec[0], X_OK) != 0)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv_exec[0]);
			last_status = 127;
			free(argv_exec);
			free(command);
			continue;
		}

		/* Execute command */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			last_status = 1;
			free(argv_exec);
			if (should_free_command)
				free(command);
			continue;
		}

		if (pid == 0)
		{
			execve(argv_exec[0], argv_exec, environ);
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv_exec[0]);
			_exit(127);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
		}

		free(argv_exec);
		if (should_free_command)
			free(command);
		else
			should_free_command = 1; /* Reset flag */
	}
	return (0);
}
