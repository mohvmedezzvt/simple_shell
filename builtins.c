#include "hsh.h"

/**
 * hsh_cd - Change the current working directory
 * @args: The arguments passed to the cd command
 *
 * Return: Always returns 1
 */
int hsh_cd(char **args)
{

	char current[PATH_MAX];
	int value = -1;

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		value = chdir(getenv("HOME"));
	}
	else if (strcmp(args[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
		if (value == -1)
		{
			getcwd(current, PATH_MAX);
			write(STDOUT_FILENO, current, strlen(current));
			write(STDOUT_FILENO, "\n", 1);

		}
	}
	else
	{
		value = chdir(args[1]);
	}

	if (value != -1)
	{
		getcwd(current, PATH_MAX);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", current, 1);
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
	(void)args;
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
