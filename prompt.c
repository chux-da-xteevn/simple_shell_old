#include "main.h"

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	char *prompt = "#cisfun$ ";

	write(STDOUT_FILENO, prompt, _strlen(prompt));
}

/**
 * _strlen - Calculate the length of a string
 * @str: The string
 *
 * Return: The length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}
