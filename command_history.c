#include "main.h"

char **command_history = NULL;
int history_count = 0;

/**
 * add_to_history - Adds a command to the history
 * @command: The command to store
 */
void add_to_history(char *command)
{
	if (command_history == NULL)
	{
		command_history = malloc(sizeof(char *) * HISTORY_SIZE);
		if (!command_history)
			return;
	}

	if (history_count < HISTORY_SIZE)
	{
		command_history[history_count] = strdup(command);
		if (command_history[history_count])
			history_count++;
	}
}

/**
 * free_command_cache - Frees the stored command history
 */
void free_command_cache(void)
{
	int i;

	if (!command_history)
		return;

	for (i = 0; i < history_count; i++)
	{
		free(command_history[i]);
	}
	free(command_history);
	command_history = NULL;
	history_count = 0;
}
