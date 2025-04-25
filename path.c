#include "main.h"
#include <sys/stat.h>

/**
 * find_in_path - Find command in PATH
 * @cmd: Command to find
 * Return: Full path or NULL
 */
char *find_in_path(char *cmd)
{
    char *path = NULL, *path_copy = NULL, *dir = NULL;
    char *full_path = NULL;
    int i = 0;
    struct stat st;

    if (cmd == NULL || *cmd == '\0')
        return (NULL);

    /* Check if command contains slash */
    if (strchr(cmd, '/'))
    {
        if (stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
            return (strdup(cmd));
        return (NULL);
    }

    /* Find PATH in environment */
    while (environ[i] != NULL)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = environ[i] + 5;
            break;
        }
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
