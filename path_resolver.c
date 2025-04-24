#include "main.h"
#include <sys/stat.h>

/**
 * is_executable - checks if a file is executable
 * @path: path to file
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(const char *path)
{
	struct stat st;

	return (stat(path, &st) == 0 && (st.st_mode & S_IXUSR));
}

/**
 * resolve_path - finds the full path of a command in $PATH
 * @command: command name
 * Return: full path or NULL if not found (malloc'd string, free it)
 */
char *resolve_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

	if (command == NULL)
		return (NULL);

	if (command[0] == '/' || command[0] == '.')
		return (strdup(command)); // already a path

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
			break;

		snprintf(full_path, len, "%s/%s", dir, command);

		if (is_executable(full_path))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
