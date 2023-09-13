#include "shell.h"

/**
 * main - Entry point
 * Return: 0 (success)
 */

int main(void)
{
	char cmd[300];

	while (true)
	{
		display_prompt();
		execute_command(cmd);
		user_input(cmd, sizeof(cmd));
	}
	return (0);
}

/**
 * display_prompt - shows the prompt on the shell
 * Return: void
 */

void display_prompt(void)
{
	kel_print("kel_shell$$ ");
}

/**
 * execute_command - executes command of the user
 * @cmd: string to be executed
 * Return: 0 on success
 */

void execute_command(const char *cmd)
{
	pid_t my_pid = fork();

	if (my_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (my_pid == 0)
	{
		execlp(cmd, cmd, (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * user_input - read command of the user
 * @cmd: string of the command
 * @size: size of string
 * Return: void
 */

void user_input(char *cmd, size_t size)
{
	if (fgets(cmd, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			kel_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			kel_print("error while reading input. \n");
			exit(EXIT_FAILURE);
		}
	}
	cmd[strcspn(cmd, "\n")] = '\0';
}
