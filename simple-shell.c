#include "shell.h"
/**
 * main - fucntion
 * Return: 0
 */
int main(void)
{
char *buff = NULL, *args[2];
size_t buffsize = 0;
ssize_t bytes;
pid_t wpid;
int wstatus;
char prompt[] = "$ ";
bool piping = false;
while (1 && !piping)
{
	piping = (isatty(STDIN_FILENO) == 0);
write(STDOUT_FILENO, prompt, _strlen(prompt));
bytes = getline(&buff, &buffsize, stdin);
if (bytes == -1)
{
exit(EXIT_FAILURE);
}
if (buff[bytes - 1] == '\n')
buff[bytes - 1] = '\0';
wpid = fork();
if (wpid == -1)
{
perror("Error ");
exit(EXIT_FAILURE);
}
if (wpid == 0)
{
args[0] = buff, args[1] = NULL;
execvp(args[0], args);
perror(args[0]);
exit(EXIT_FAILURE);
}
if (waitpid(wpid, &wstatus, 0) == -1)
{
perror("Error (wait)");
exit(EXIT_FAILURE);
}
}
free(buff);
return (0);
}
