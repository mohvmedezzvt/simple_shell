#include "hsh.h"

/**
 * main - Entry point of the simple shell program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 *
 * Return: The exit status of the shell program
 */
int main(int argc, char **argv)
{
	FILE *input_file;
	char *line = NULL, **args;
	size_t bufsize = 0;
	int status = 0;

	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
		hsh_loop();
	else
	{
		input_file = stdin;
		while (getline(&line, &bufsize, input_file) != -1)
		{
			line[strcspn(line, "\n")] = '\0';
			args = hsh_parse_line(line);
			status = hsh_execute(args);

			free(args);
			if (status == 0)
				break;
		}


		free(line);
	}
	if (status == 127)
		return (127);
	else
		return (EXIT_SUCCESS);
}


/**
 * hsh_loop - Run the shell program in interactive mode
 */
void hsh_loop(void)
{
	char *line, **args;
	int status;

	do {
		printf("#cisfun: ");
		line = hsh_read_line();
		args = hsh_parse_line(line);
		status = hsh_execute(args);

		free(line);
		free(args);
	} while (status);
}
