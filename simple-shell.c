#include "shell.h"
/**
 * main - fucntion
 * Return: 0
 */
int main(void)
{
char *buff = NULL, *p = "($) ";
size_t buffsize = 0;
ssize_t bytes;
pid_t wpid;
int wstatus;

bool from_pipe = false;
while (1 && !from_pipe)
{
if (isatty(STDIN_FILENO) == 0)
from_pipe = true;
write(STDOUT_FILENO, p, 4);
bytes = getline(&buff, &buffsize, stdin);
if (bytes == -1)
{
perror("Exit");
free(buff);
exit(EXIT_FAILURE);
}
if (buff[bytes - 1] == '\n')
buff[bytes - 1] = '\0';
wpid = fork();
if (wpid == -1)
{
perror("Error (fork)");
exit(EXIT_FAILURE);
}
if (wpid == 0)
execvp(buff, &buff);
if (waitpid(wpid, &wstatus, 0) == -1)
{
perror("Error (wait)");
exit(EXIT_FAILURE);
}
}
free(buff);
return (0);
}
