#include "main.h"

/**
 * prompt - Displays shell prompt.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("#cisfun$ ");
	fflush(stdout);
}
