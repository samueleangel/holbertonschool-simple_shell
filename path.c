#include "main.h"

#include "main.h"
#include <sys/stat.h>

/**
 * find_in_path - Find command in PATH
 * @cmd: Command to find
 * Return: Full path or NULL
 */
char *find_in_path(char *cmd)
{
	char *path = NULL;
	char *path_copy = NULL;
	char *dir = NULL;
	char *full_path = NULL;
	int i = 0;
	struct stat st;

	/* Find PATH in environment */
	while (environ[i] != NULL && path == NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			path = environ[i] + 5;
		i++;
	}

	if (path == NULL || *path == '\0')
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	full_path = malloc(1024);
	if (full_path == NULL)
	{
		free(path_copy);
		return (NULL);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, 1024, "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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
