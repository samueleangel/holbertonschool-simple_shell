#include "main.h"

/**
 * print_env - Prints the environment variables
 */
void print_env(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
