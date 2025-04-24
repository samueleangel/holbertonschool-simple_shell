#include "main.h"

/**
 * read_command - Reads user input.
 * @command: Buffer to store input.
 * @len: Size of buffer.
 * Return: Command string or NULL.
 */
char *read_command(char **command, size_t *len)
{
	ssize_t read_chars = getline(command, len, stdin);

	if (read_chars == -1)
		return (NULL);

	if ((*command)[read_chars - 1] == '\n')
		(*command)[read_chars - 1] = '\0';

	return (*command);
}
