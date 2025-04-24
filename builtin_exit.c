#include "main.h"

/**
 * builtin_exit - Exits the shell without handling arguments.
 * @args: Unused argument (required for function signature).
 */
void builtin_exit(char **args)
{
	(void)args;
	free_command_cache();
	exit(0);
}
