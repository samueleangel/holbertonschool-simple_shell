#include "main.h"

/**
 * print_env - Prints the environment variables
 */
void print_env(void)
{
	int i = 0;
	size_t len;

	while (environ[i] != NULL)
	{
		len = strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
