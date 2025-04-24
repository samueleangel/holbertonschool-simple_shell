#include "main.h"

/**
 * builtin_exit - Exits the shell without handling arguments
 */
void builtin_exit(void)
{
	free_command_cache();
	_exit(0);
}
