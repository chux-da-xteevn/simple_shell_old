#include "main.h"

/**
 * get_process_id - Get the process ID of the current process
 *
 * Return: The process ID on success, -1 on failure.
 */
pid_t get_process_id(void)
{
	pid_t pid;

	pid = getpid();
	if (pid == -1)
	{
		perror("getpid");
		return (-1);
	}

	return (pid);
}
