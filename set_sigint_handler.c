#include "main.h"

/**
 * sigint_handler - Custom handler for SIGINT
 * @sig: Signal number
 */

void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
	fflush(stdout);
}

void set_sigint_handler(void)
{
	signal(SIGINT, sigint_handler);
}
