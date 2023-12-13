#include "shell.h"

/**
 * handler- handles signals and print the prompt
 * @signum: signal to handle
 *
 * Return: void
 */

void handler(int signum)
{
	(void) signum;

	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * main- emulation of Shell with limited functionality
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 *
 * Return: 0 on success, 1 if failure
 */

int main(int argc, char **argv, char **env) /* checkout execve man page */
{
	char *buffer, **cmds;
	size_t len;
	ssize_t stringoftext;
	char *prompt = "$ ", *exitcmd = "exit", *envcmd = "env";
	pid_t pid;
	struct stat getfileStatus;
	int status, number;
	(void)argc;

	buffer = NULL, len = 0, number = 0;

	if (isatty(STDIN_FILENO))  /* testing if fd is associated with hsh */
		write(STDOUT_FILENO, prompt, 2); /* write takes 3 args */
/* fd, pointer to buf where data is stored, # of bytes to write from buffer */

	signal(SIGINT, handler); /* signal kill: ctrl + c */
/* sends SIGINT signal that stops process & ends never ending while loop */

	while ((stringoftext = getline(&buffer, &len, stdin))) /* loop 4ever */
	{
		if (stringoftext == EOF)
			eof_constant(buffer);
		++number;

		cmds = stringtokarray(buffer);
		pid = fork(); /* create a new process */

		if (pid == -1)
		{
			fork_fail();
		}
		if (pid == 0)
		{
			/* check if commands is NULL or all empty spaces */
			if (cmds == NULL)
				cmds_is_null(buffer);
			/* search to see if command is EXIT to exit the shell */
			else if (_strcmp(exitcmd, cmds[0]))
				exitfree(buffer, cmds);
			/* search to see if command is ENV to print variables */
			else if (_strcmp(envcmd, cmds[0]))
				envfree(buffer, cmds, environ);
			/* check if command is full path to a executable file */
			else if (stat(cmds[0], &getfileStatus) == 0)
			{
				execve(cmds[0], cmds, NULL);
			}
			/* check all directories in PATH for executable cmds */
			else
				absPath(cmds, buffer, env, argv, number);
		}
		else
		{
			wait(&status); /* waits for child to finish */
/* stores address of status: kill unneccessary bc child wont make zombies */
			if (cmds == NULL)
			{
				free(buffer);
				free_doubleptr(cmds);
			}
			else if (_strcmp(exitcmd, cmds[0]))
				exitfree(buffer, cmds);
			else
				free(buffer);
			free_doubleptr(cmds);

			len = 0, buffer = NULL;

			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, prompt, 2);
		}
	}
	if (stringoftext == -1)
		return (EXIT_FAILURE); /* macro: this is 1 */
	else
		return (EXIT_SUCCESS); /* macro: this is 0 */
}}
