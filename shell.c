#include "shell.h"

/**
 * main - Entry point
 * Return: 0 (success)
 */

int main(void)
{
	char cmd[350];

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
	printf("simple_shell$$ ");
}

/**
 * execute_command - executes command of the user
 * @cmd: string to be executed
 * Return: 0 on success
 */

void execute_command(const char *cmd)
{
	pid_t my_pid = fork();
	char *args[] = {cmd, NULL};

	if (my_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (my_pid == 0)
	{
		char cmd_path[300];

		snprintf(cmd_path, sizeof(cmd_path), "/bin/%s", cmd);

		execve(cmd_path, args, NULL);

		perror("execve");
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
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("fgets");
			exit(EXIT_FAILURE);
		}
	}
	cmd[strcspn(cmd, "\n")] = '\0';
}
