#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - Body of the program
 *
 * Return: 0 on success
 */
int main(void)
{
	pid_t pid;

	printf("Before fork\n");

	pid = fork();

	if (pid == -1)
	{
		perror("Error in fork");
		return (1);
	}

	if (pid > 0)
	{

		printf("Parent process. PID: %d\n", getpid());


		int status;
		wait(&status);

		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		}
	}
	else
	{

		printf("Child process. PID: %d\n", getpid());
		printf("Child process is doing some work...\n");


		sleep(3);

		printf("Child process finished\n");

		exit(42);
	}

	printf("After fork\n");

	return (0);
}
