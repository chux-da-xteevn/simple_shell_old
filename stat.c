#include "main.h"

/**
 * get_file_info - Get information about a file
 * @filename: The name of the file
 * @info: Pointer to a structure to store file information
 *
 * Return: On success, return 0. On failure, return -1.
 */
int get_file_info(const char *filename, struct stat *info)
{
	if (stat(filename, info) == -1)
	{
		perror("stat");
		return (-1);
	}

	return (0);
}
