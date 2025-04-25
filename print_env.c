#include "main.h"

/**
 * print_env - Prints the environment variables
 */
void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
