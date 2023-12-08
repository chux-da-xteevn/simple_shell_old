#include "main.h"

/**
 * get_parent_process_id - Get the parent process ID of the current process
 *
 * Return: The parent process ID on success, -1 on failure.
 */
pid_t get_parent_process_id(void)
{
	pid_t ppid;

	ppid = getppid();
	if (ppid == -1)
	{
		perror("getppid");
		return (-1);
	}

	return (ppid);
}
