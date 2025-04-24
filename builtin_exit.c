#include "main.h"

/**
 * builtin_exit - Exits the shell
 * @args: Arguments (unused here)
 */
void builtin_exit(char **args)
{
	(void)args;
	exit(0);
}
