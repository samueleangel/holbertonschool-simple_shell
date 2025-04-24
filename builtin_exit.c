#include "main.h"

/**
 * builtin_exit - Exits the shell with status.
 * @args: Arguments (args[1] = exit status).
 */
void builtin_exit(char **args)
{
	int status = 0;

	if (args[1])
		status = atoi(args[1]);

	free_command_cache();
	exit(status);
}
