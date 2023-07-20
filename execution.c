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
	if (args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			perror("hsh");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("hsh");
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
