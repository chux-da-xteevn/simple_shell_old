#include "main.h"

/**
 * execute - Execute a command
 * @cmd: The command to execute
 *
 * Return: On success, return 0. On failure, return -1.
 */
int execute(char *cmd)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}

	if (pid == 0)
	{

		if (execve(cmd, NULL, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{

		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (0);
}
