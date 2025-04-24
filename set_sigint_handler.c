#include "main.h"

/**
 * sigint_handler - Handles Ctrl+C.
 * @sig: Signal number.
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
	fflush(stdout);
}

/**
 * set_sigint_handler - Sets Ctrl+C handler.
 */
void set_sigint_handler(void)
{
	signal(SIGINT, sigint_handler);
}
