#include "main.h"

/**
 * main - Simple shell program
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf(":) ");
		line = read_line();
		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);

	return (0);
}

/**
 * execute - Execute a command
 * @args: Array of arguments
 *
 * Return: 1 on success, 0 on exit.
 */
int execute(char **args)
{
	pid_t pid;
	int status;
	char *path = "/bin/";

	if (args[0] == NULL)
		return (1);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			args[0] = str_concat(path, args[0]);
			if (execve(args[0], args, NULL) == -1)
			{
				perror("shell");
			}
			free(args[0]);
		}
		_exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}

	return (1);
}
