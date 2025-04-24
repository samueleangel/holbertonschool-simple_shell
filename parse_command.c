#include "main.h"

/**
 * parse_command - Splits command into args.
 * @command: Command string.
 * Return: NULL-terminated array of args.
 */
char **parse_command(char *command)
{
	char **argv, *token;
	int i = 0, bufsize = 64;

	argv = malloc(sizeof(char *) * bufsize);
	if (!argv)
		return (NULL);

	token = strtok(command, " ");
	while (token)
	{
		argv[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			argv = realloc(argv, sizeof(char *) * bufsize);
			if (!argv)
				return (NULL);
		}
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	return (argv);
}

