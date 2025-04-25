#include "main.h"
#include <unistd.h>

/**
 * print_env - Print environment variables
 */
void print_env(void)
{
	extern char **environ;
	int i = 0;
	size_t len;

	if (environ == NULL)
		return;

	while (environ[i] != NULL)
	{
		len = strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
