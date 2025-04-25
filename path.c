#include "main.h"
#include <sys/stat.h>

/**
 * find_in_path - Enhanced PATH resolution
 * @cmd: Command to locate
 * Return: Full path or NULL
 */
char *find_in_path(char *cmd)
{
	char *path = NULL, *path_copy = NULL, *dir = NULL;
	char *full_path = NULL;
	int i = 0;
	struct stat st;

	/* 1. Handle empty command */
	if (cmd == NULL || *cmd == '\0')
		return (NULL);

	/* 2. Absolute path handling */
	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
			return (strdup(cmd));
		return (NULL);
	}

	/* 3. Locate PATH variable */
	while (environ[i] && !path)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			path = environ[i] + 5;
		i++;
	}

	/* 4. Handle empty PATH */
	if (!path || *path == '\0')
		return (NULL);

	/* 5. Search through PATH */
	path_copy = strdup(path);
	full_path = malloc(1024);
	if (!path_copy || !full_path)
	{
		free(path_copy);
		free(full_path);
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, 1024, "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	/* 6. Cleanup */
	free(full_path);
	free(path_copy);
	return (NULL);
}
