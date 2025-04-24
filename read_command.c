#include "main.h"

#define  READ_SIZE 1024

/**
 * read_command - Reads user input.
 * @command: Buffer to store input.
 * @len: Size of buffer.
 * Return: Command string or NULL.
 */
char *read_command(char **command, size_t *len)
{
	static char buffer[READ_SIZE];
	ssize_t bytes_read;
	char *new_command = NULL;
	size_t total_len = 0;

	if (*command == NULL)
		*len = 0;

	while ((bytes_read = read(STDIN_FILENO, buffer, READ_SIZE-1)) > 0)
	{	
		buffer[bytes_read] = '\0';
		new_command = realloc(*command, *len + bytes_read + 1);
		if (!new_command)
		{
			free(*command);
			return NULL;
		}

		*command = new_command;
		strcpy(*command + *len, buffer);
		*len += bytes_read;
		
		if (strchr(buffer, '\n'))
			break;
	}
	if (bytes_read <= 0 && *len == 0)
		return (NULL);

	if (*len > 0 && (*command)[*len-1] == '\n')
	{
		(*command){*len-1} = '\0';
		(*len)--;
	}
	
	return *command;
}
