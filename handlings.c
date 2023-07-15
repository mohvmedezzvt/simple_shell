#include "hsh.h"

/**
 * hsh_read_line - Read a line of input from the user
 *
 * Return: The read line as a string
 */
char *hsh_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * hsh_parse_line - Parse a line into an array of tokens
 * @line: The input line to be parsed
 *
 * Return: An array of tokens (strings)
 */
char **hsh_parse_line(char *line)
{
	char **tokens, *token;
	int bufsize = TOK_BUFSIZE, i = 0;

	tokens = malloc(bufsize * sizeof(char *));
	if (tokens == NULL)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIMETER);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (tokens == NULL)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOK_DELIMETER);
	}

	tokens[i] = NULL;
	return (tokens);
}


/**
 * hsh_get_path_directories - Get an array of directories in
 * the PATH environment variable
 *
 * Return: An array of directories (strings)
 */
char **hsh_get_path_directories()
{
	char *path, *token, **directories;
	int bufsize = TOK_BUFSIZE, i = 0;

	path = getenv("PATH");
	directories = malloc(bufsize * sizeof(char *));
	if (!directories)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		directories[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			directories = realloc(directories, bufsize * sizeof(char *));
			if (!directories)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, ":");
	}

	directories[i] = NULL;
	return (directories);
}

/**
 * hsh_launch - Launch a process and execute a command
 * @args: The arguments of the command
 *
 * Return: Always returns 1
 */
int hsh_launch(char **args)
{
	char *envp[] = {NULL}, **directories, *path;
	pid_t pid;
	int status, i = 0;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			directories = hsh_get_path_directories();
			while (directories[i] != NULL)
			{
				path = malloc(strlen(directories[i]) + strlen(args[0]) + 2);
				if (!path)
				{
					fprintf(stderr, "Allocation error\n");
					exit(EXIT_FAILURE);
				}
				sprintf(path, "%s/%s", directories[i], args[0]);
				if (execve(path, args, envp) == 0)
				{
					free(path);
					free(directories);
					exit(EXIT_SUCCESS);
				}
				free(path);
				i++;
			}
			free(directories);
			exit(127);
		}
	} else if (pid < 0)
		perror("hsh");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			return (127);
		}
	}
	return (1);
}
