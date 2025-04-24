#include "main.h"

/**
 * read_command - Reads a command from standard input
 * @command: Pointer to the command string
 * @len: Pointer to the length of the buffer
 *
 * Return: The command string, or NULL on failure
 */
char *read_command(char **command, size_t *len)
{
	ssize_t read;

	read = getline(command, len, stdin);

	if (read == -1)
		return (NULL);

	if ((*command)[read - 1] == '\n')
		(*command)[read - 1] = '\0';

	return (*command);
}
