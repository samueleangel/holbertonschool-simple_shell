#include "main.h"

#define READ_SIZE 1024

/**
 * read_command - Read user input
 * Return: Command string or NULL
 */
char *read_command(void)
{
	static char buffer[READ_SIZE];
	ssize_t bytes_read;
	char *command = NULL;
	char *newline = NULL;

	bytes_read = read(STDIN_FILENO, buffer, READ_SIZE - 1);
	if (bytes_read <= 0)
		return (NULL);

	buffer[bytes_read] = '\0';
	newline = strchr(buffer, '\n');
	if (newline != NULL)
		*newline = '\0';

	command = malloc(strlen(buffer) + 1);
	if (command == NULL)
		return (NULL);

	strcpy(command, buffer);
	return (command);
}
