#include "hsh.h"

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
		}
	}
	if (getcwd(current, PATH_MAX) == NULL)
	{
		perror("getcwd");
	}
	if (setenv("PWD", current, 1) == -1)
	{
		perror("setenv");
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
	char *c;

	if (args[1] != NULL)
	{
		for (c = args[1]; *c != '\0'; c++)
		{
			if (!isdigit(*c))
			{
				fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", args[1]);
				exit(2);
				return (2);
			}
		}

		exit_status = atoi(args[1]);
		if (exit_status < 0)
		{
			fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", args[1]);
			exit(2);
			return (2);
		}
	}

	exit(exit_status);
	return (exit_status);
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
 * hsh_setenv - Set a new environment variable or modify an existing one.
 * @args: The arguments passed to the setenv command.
 *
 * Return: Always returns 1
 */
int hsh_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv");
		return (1);
	}

	return (1);
}

/**
 * hsh_unsetenv - Unset an environment variable.
 * @args: The arguments passed to the unsetenv command.
 *
 * Return: Always returns 1
 */
int hsh_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		return (1);
	}

	return (1);
}