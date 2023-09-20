#include "shell.h"
#define BUFFER_SIZE 1024
#define MAX_ARGS 10

int main(void)
{
    char *buff = NULL;
    size_t buffsize = 0;
    ssize_t bytes;
    pid_t wpid;
    int wstatus;
    char prompt[] = "$ ";
    bool piping = false;

    while (1 && !piping)
    {
        piping = (isatty(STDIN_FILENO) == 0);
        write(STDOUT_FILENO, prompt, strlen(prompt));
        bytes = getline(&buff, &buffsize, stdin);

        if (bytes == -1)
        {
            perror("Error (getline)");
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
        else if (wpid == 0)
        {
            char *args[MAX_ARGS];
            char *token;
            int argIndex = 0;

            token = strtok(buff, " ");
            while (token != NULL && argIndex < MAX_ARGS - 1)
            {
                args[argIndex] = token;
                argIndex++;
                token = strtok(NULL, " ");
            }
            args[argIndex] = NULL;

            execvp(args[0], args);
            perror("Error ");
            exit(EXIT_FAILURE);
        }
        else if (waitpid(wpid, &wstatus, 0) == -1)
        {
            perror("Error (wait)");
            exit(EXIT_FAILURE);
        }
    }

    free(buff);
    return 0;
}
