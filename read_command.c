#include "main.h"

#define READ_SIZE 1024

/**
 * read_command - Reads user input.
 * @command: Buffer to store input.
 * @len: Size of buffer.
 * Return: Command string or NULL.
 */
char *read_command(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	char *command = NULL;
	size_t cmd_len = 0;
	char *newline_pos
	
	char *newline_pos = NULL;
	bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE -1);
	if(bytes_read <= 0)
		return (NULL);

	buffer[bytes_read] = '\0';

	newline_pos = strchr(buffer, '\n');
	if (newline_pos)
		*newline_pos = '\0';
	else
		newline_pos = buffer + bytes_read;

	cmd_len = newline_pos - buffer;
	command = malloc(cmd_len + 1);
	if (!command)
		return (NULL);

	strncpy(command, buffer, cmd_len);
	command[cmd_len] = '\0';

	return (command);
}
