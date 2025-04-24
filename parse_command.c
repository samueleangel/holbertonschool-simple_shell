#include "main.h"

/**
 * parse_command - Splits a command string into arguments
 * @command: The command string
 *
 * Return: A NULL-terminated array of strings (arguments)
 */
char **parse_command(char *command)
{
	char **argv;
	char *token;
	int i = 0;
	int bufsize = 64;

	argv = malloc(sizeof(char *) * bufsize);
	if (!argv)
		return (NULL);

	token = strtok(command, " ");
	while (token != NULL)
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
