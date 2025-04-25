#include "main.h"

#define MAX_ARGS 128

/**
 * parse_command - Splits command into args.
 * @command: Command string.
 * Return: NULL-terminated array of args.
 */
char **parse_command(char *command)
{
	char **argv, *token;
	int i = 0;

	argv = malloc(sizeof(char *) * MAX_ARGS);
	if (!argv)
		return (NULL);

	token = strtok(command, " ");
	while (token && i < MAX_ARGS - 1)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	return (argv);
}
