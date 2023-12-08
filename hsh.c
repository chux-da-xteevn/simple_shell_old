#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 1024

/**
 * sigint_handler - This Handles the SIGINT signal (Ctrl+C)
 * @signo: The Signal number
 */
void sigint_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
 * main - Code for Simple shell program
 *
 * Return: upon success 0
 */
int main(void)
{
	char *buffer = NULL;
	size_t len = 0;
	ssize_t read_status;
	pid_t child_pid;
	int status;

	signal(SIGINT, sigint_handler);

	while (1)
	{
		write(STDOUT_FILENO, "($) ", 5);
		read_status = getline(&buffer, &len, stdin);

		if (read_status == -1)
		{
			perror("Error reading command");
			exit(EXIT_FAILURE);
		}

		if (read_status == 1) /* Ctrl+D (EOF) */
		{
			write(STDOUT_FILENO, "\n", 1);
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		buffer[read_status - 1] = '\0';

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error forking");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{
			if (execve(buffer, NULL, NULL) == -1)
			{
				perror(buffer);
				free(buffer);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(child_pid, &status, 0);

			if (WIFEXITED(status))
				continue;
			else if (WIFSIGNALED(status))
				fprintf(stderr, "Child process terminated by signal %d\n", WTERMSIG(status));
		}
	}

	return (0);
}
