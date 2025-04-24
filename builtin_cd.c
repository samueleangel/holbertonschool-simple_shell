#include "main.h"

/**
 * builtin_cd - Changes directory.
 * @args: Arguments (args[1] = target dir).
 */
void builtin_cd(char **args)
{
	char *dir = args[1] ? args[1] : getenv("HOME");
	char cwd[1024];

	if (!dir)
	{
		fprintf(stderr, "cd: No HOME directory set\n");
		return;
	}

	if (chdir(dir) != 0)
		perror("cd");
	else if (getcwd(cwd, sizeof(cwd)))
		printf("Now in: %s\n", cwd);
}
