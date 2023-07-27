#include "hsh.h"

/**
 * hsh_num_builtins - Get the number of built-in commands
 *
 * Return: The number of built-in commands
 */
int hsh_num_builtins(void)
{
	char *builtin_str[] = {
	"cd",
	"exit",
	"env"
	};

	return (sizeof(builtin_str) / sizeof(char *));
}

/**
 * hsh_cd - Change the current working directory
 * @args: The arguments passed to the cd command
 *
 * Return: Always returns 1
 */
int hsh_cd(char **args)
{
	char *home;
	char *old;
	char current[PATH_MAX];

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "cd: %s\n", "HOME not set");
			return (1);
		}
		if (chdir(home) == -1)
			perror("cd");
	} else if (strcmp(args[1], "-") == 0)
	{
		old = getenv("OLDPWD");
		if (!old)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (1);
		}
		if (chdir(old) == -1)
			perror("cd");
	} else
	{
		if (chdir(args[1]) == -1)
		{
			perror("cd");
			return (1);
		}
	}

	if (getcwd(current, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (1);
	}

	if (setenv("PWD", current, 1) == -1)
	{
		perror("setenv");
		return (1);
	}

	return (1);
}

/**
 * hsh_exit - Exit the simple shell program
 * @args: The arguments passed to the exit command
 *
 * Return: Always returns 0
 */
int hsh_exit(char **args)
{
	int exit_status = 0;

	if (args[1] != NULL)
		exit_status = atoi(args[1]);

	exit(exit_status);
	return (0);
}

/**
 * hsh_env - Print the current environment
 * @args: The arguments passed to the env command (ignored)
 *
 * Return: Always returns 1 to continue the shell loop
 */
int hsh_env(char **args)
{
	int i = 0;

	(void)args;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (1);
}

/**
 * hsh_execute - Execute a command by launching a process or
 * running a built-in command
 * @args: The arguments of the command
 *
 * Return: The exit status of the command
 */
int hsh_execute(char **args)
{
	int i;
	char *builtin_str[] = {
		"cd",
		"exit",
		"env"
	};
	int (*builtin_func[]) (char **) = {
		&hsh_cd,
		&hsh_exit,
		&hsh_env
	};

	if (args[0] == NULL)
		return (1);

	for (i = 0; i < hsh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return ((*builtin_func[i])(args));
	}

	return (hsh_launch(args));
}
