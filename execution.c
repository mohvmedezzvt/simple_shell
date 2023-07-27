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
	"env",
	"setenv",
	"unsetenv"
	};

	return (sizeof(builtin_str) / sizeof(char *));
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
		"env",
		"setenv",
		"unsetenv"
	};
	int (*builtin_func[]) (char **) = {
		&hsh_cd,
		&hsh_exit,
		&hsh_env,
		&hsh_setenv,
		&hsh_unsetenv
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
