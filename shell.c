#include "shell.h"

/**
 * main - The main function carrying the program
 *
 * Return: Always 0 to indicate successful execution.
 */
int main(void)
{
	size_t size_prompt;

	char *prompt;

	int status;

	size_prompt = 0;

	prompt = NULL;

	status = 0;

	if (!isatty(0))
	{
		while (getline(&prompt, &size_prompt, stdin) != -1)
		{
			nonInteractMode(prompt, &status);
		}
		if (prompt)
		{
			free(prompt);
			prompt = NULL;
		}
		return (status);
	}
	startMyshell();
	return (0);
}
