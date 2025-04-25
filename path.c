#include "main.h"

extern char **environ;

/**
 * find_in_path - Finds command in PATH without getenv.
 * @cmd: Command to search.
 * Return: Full path or NULL.
 */
char *find_in_path(char *cmd)
{
	char *path = NULL, *path_copy, *dir, *full_path;
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
		i++;
	}

	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	full_path = malloc(1024);
	if (!full_path)
	{
		free(path_copy);
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, 1024, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(full_path);
	free(path_copy);
	return (NULL);
}
